/**
 * file: src/octree/fill_oct.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <octree/fill_oct.h>

#if !defined(CLASSIC_MODE) && defined(FILL_SOLIDS)

// ##### FillOct() ###################################################
FillOct::FillOct(IndexOct idxOct)
  : IndexOct(idxOct), fillPoints(idxOct.getMaxTreeHight()) 
#ifdef LIMITED_STACK
  , keptPoint(NULL_NODE_VEC)
#endif // LIMITED_STACK
{
}

// ##### add() #######################################################
void FillOct::add(NodeIndex idx) {
  assert (isIn(idx, idx.getHight()));
  assert (isLeaf(idx));
  assert (!fillPoints.isFull());
  
  if (getColor(idx) == UNDEF_OBJ) {
    setColor(idx, fillColor);
    fillPoints.put(idx);
  }
}

// ##### fill() ######################################################
void FillOct::fill(OctGen* generator) {
  assert (generator != NULL);

  fillTree(getTree(), NodeIndex(0, 0, 0, getMaxTreeHight()), generator);
  cout << endl;
}

// ##### fill() 
void FillOct::fill() {
  while (!fillPoints.isEmpty()) {
    NodeIndex idx= fillPoints.get();
    assert (isIn(idx, idx.getHight()));
    assert (isLeaf(idx));
    
    AxIndex max= (1 << (getMaxTreeHight() - idx.getHight())) - 1;
    for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
      AxIndex pos= idx[ax];
      NodeIndex neighbor= idx;
      if (pos < max) {
	neighbor.setCoordinate(ax, pos + 1);
	fillParts(neighbor, ax, 0);
      }
      if (pos > 0) {
	neighbor.setCoordinate(ax, pos - 1);
	fillParts(neighbor, ax, 1);
      }
    }
  }
}

// ##### fillParts() #################################################
void FillOct::fillParts(NodeIndex myIdx,
			Axis axis, AxIndex partOfs) {
  _octree subtree;
  Hight h= getExistNode(myIdx, subtree);
  myIdx.setHight(h);
  fillParts(subtree, myIdx, axis, partOfs);
}

// ##### fillParts() 
void FillOct::fillParts(_octree subtree, NodeIndex myIdx,
			Axis axis, AxIndex partOfs) {
  if (OctStruct::isLeaf(*subtree)) {
    if (!fillPoints.isFull()) {
      assert (!fillPoints.isFull());
      add(myIdx);
    } else {
      if (isUndefObj(*subtree)) {
#ifdef MARK_BORDER
	OctStruct::setBorderColor(*subtree, fillColor);
#elif defined(LIMITED_STACK)
	fillFurther= true;
	keptPoint= myIdx;
#endif // LIMITED_STACK && !MARK_BORDER
      }
    }
  } else {
    for(PartType i= 0; i < OCT_PARTS; ++i) {
      if (getPartOfs(i, axis) == partOfs) {
        fillParts(OctStruct::getChild(subtree, i), getChild(myIdx, i), 
                  axis, partOfs);
      }
    }
  }
}

// ##### fillTree() ##################################################
void FillOct::fillTree(_octree subtree, NodeIndex myIdx, OctGen* generator) {
  assert (isIn(myIdx));

  if (OctStruct::isLeaf(*subtree)) {
#ifndef NDEBUG
    Color c= OctStruct::getColor(*subtree);
#endif // !NDEBUG
#ifdef MARK_BORDER
    if (isBorderNode(*subtree)) {
      assert (c > UNDEF_OBJ && c < NO_OBJECT);
      fillColor= OctStruct::getBorderColor(*subtree);
      assert (fillColor >= 0);
      assert (fillPoints.isEmpty());

      OctStruct::setColor(*subtree, fillColor);
      add(myIdx);
      fill();
      return;
    }
#endif // MARK_BORDER

    if (isUndefObj(*subtree)) {
      assert (c == UNDEF_OBJ);
      assert (isIn(myIdx, myIdx.getHight()));
#ifdef SAVED_FILL
      bool savedFill;
      fillColor= getColor(generator, myIdx, savedFill);
      assert (fillColor >= 0);
      cerr << ".";
      if (!savedFill) {
	OctStruct::setColor(*subtree, fillColor);
	return;
      }
#else // !SAVED_FILL
      fillColor= generator->getColor(myIdx);
      assert (fillColor >= 0);
#endif // !SAVED_FILL

#ifdef LIMITED_STACK
      do {
        fillFurther= false;
#endif // LIMITED_STACK
       assert (fillPoints.isEmpty());
       add(myIdx);
       fill();
#ifdef LIMITED_STACK
        if (fillFurther) {
          assert (fillPoints.isEmpty());
	  cerr << ".";
          myIdx= keptPoint;
        }
      } while (fillFurther);
#endif // LIMITED_STACK

    }
  } else {
    for (PartType i= 0; i < OCT_PARTS; ++i) {
      fillTree(OctStruct::getChild(subtree, i), getChild(myIdx, i), 
               generator);
    }
  }
}

#ifdef SAVED_FILL
// ##### getColor() ##################################################
Color FillOct::getColor(OctGen* generator, NodeIndex p, bool &savedFill) {
  savedFill= true; 
  Color pColor= generator->getColor(p);

  if (p.getHight() != BASE_NODE_HIGHT) {
    // sollte auf jeden Fall sicher sein :-)
    return pColor;
  }

  // Knoten liegt auf unterster Ebene 
  // ==> gibt nur einen Nachbar in jede Richtung
  AxIndex max= (1 << getMaxTreeHight()) - 1;
  for (Axis i= 0; i < DIMENSIONS; ++i) {
    AxIndex pos= p[i];
    NodeIndex neighbor= p;
    if (pos < max) {
      neighbor.setCoordinate(i, pos + 1);
      neighbor= getExistNode(neighbor);
      assert (isLeaf(neighbor));
      Color nColor= IndexOct::getColor(neighbor);
      if (nColor== UNDEF_OBJ) {
	nColor= generator->getColor(neighbor); 
      }
      if (nColor == NO_OBJECT) {
	savedFill= (pColor == NO_OBJECT);
	return pColor; 
      }
      if (nColor != pColor) {
	savedFill= false;
	return pColor;
      }
    }
    neighbor= p;
    if (pos > 0) {
      neighbor.setCoordinate(i, pos - 1);
      neighbor= getExistNode(neighbor);
      assert (isLeaf(neighbor));
      Color nColor= IndexOct::getColor(neighbor);
      if (nColor== UNDEF_OBJ) {
	nColor= generator->getColor(neighbor); 
      }
      if (nColor == NO_OBJECT) {
	savedFill= (pColor == NO_OBJECT);
	return pColor; 
      }
      if (nColor != pColor) {
	savedFill= false;
	return pColor;
      }
    }
  }
  return pColor;
}
#endif // SAVED_FILL

#endif // !CLASSIC_MODE && FILL_SOLIDS

// EOF: src/octree/fill_oct.cpp

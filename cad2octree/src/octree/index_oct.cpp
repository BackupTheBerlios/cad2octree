/**
 * file: src/octree/index_oct.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <octree/index_oct.h>

#include <generator/oct_gen.h>

#include <assert.h>

// ##### IndexOct() ##################################################
IndexOct::IndexOct(Hight maxTreeHight) throw(NotEnoughMemoryException*)
  : OctStruct(), rootHight(maxTreeHight) {
}

// ##### add() #######################################################
void IndexOct::add(NodeIndex p, Color color)
    throw (NotEnoughMemoryException*) {
  _octree subtree;
  Hight h= getExistNode(p, subtree);

  assert (subtree != NULL);
  
  if (isIn(p, h) && !OctStruct::isLeaf(*subtree)) {
    assert (false);
    return;
  }

  while (h > p.getHight()) {
    --h;
    subtree->parts= createLeafs();
    subtree= OctStruct::getChild(subtree, getPart(p, h - p.getHight()));
  }

  if (OctStruct::getColor(*subtree) != color) {
    OctStruct::setColor(*subtree, color);
    ++countBorderNodes;
  }
}

// ##### add() 
void IndexOct::add(Surface *s, Color color)
    throw (NotEnoughMemoryException*) {
  assert (s != NULL);
  assert (s->getHight() == BASE_NODE_HIGHT);

  add(getTree(), NodeIndex(0, 0, 0, getMaxTreeHight()), s, color);
}

// ##### add() 
void IndexOct::add(_octree subtree, NodeIndex myIdx, Surface* s, Color color)
    throw (NotEnoughMemoryException*) {
  assert (isIn(myIdx));

  if (!s->isIn(GeomPoint(myIdx))) {
    return;
  }
  if (myIdx.getHight() == BASE_NODE_HIGHT) {
    OctStruct::setColor(*subtree, color);
    return;
  }

  if (OctStruct::isLeaf(*subtree)) {
    subtree->parts= createLeafs();
  }
  for (PartType i= 0; i < OCT_PARTS; ++i) {
    add(OctStruct::getChild(subtree, i), getChild(myIdx, i), s, color);
  }
}

// ##### exist() #####################################################
bool IndexOct::exist(NodeIndex p) {
  _octree subtree;
  Hight h= getExistNode(p, subtree);
  return isIn(p, h);
}

// ##### getChild() ##################################################
NodeIndex IndexOct::getChild(NodeIndex parent, PartType i) {
  assert (parent.getHight() != BASE_NODE_HIGHT);
  assert (isIn(parent));

  return NodeIndex((parent.getX() << 1) + getPartOfs(i, X_AXIS),
		   (parent.getY() << 1) + getPartOfs(i, Y_AXIS),
		   (parent.getZ() << 1) + getPartOfs(i, Z_AXIS),
		   parent.getHight() - 1);
}

// ##### getColor() ##################################################
Color IndexOct::getColor(NodeIndex p) {
  Node* nodePtr;
  getExistNode(p, nodePtr);
  return OctStruct::getColor(*nodePtr);
}

// ##### getExistNode() ##############################################
Hight IndexOct::getExistNode(NodeIndex p, _octree &subtree) {
  assert (isIn(p, p.getHight()));
  assert (OctStruct::exist(getTree()));

  subtree= getTree();
  Hight h= getMaxTreeHight();
  while (h > p.getHight() && !OctStruct::isLeaf(*subtree)) {
    --h;
    subtree= OctStruct::getChild(subtree, getPart(p, h - p.getHight()));
  }
  
  assert (OctStruct::exist(subtree));
  assert (0 <= h && h <= getMaxTreeHight());
  return h;
}

// ##### getExistNode() 
NodeIndex IndexOct::getExistNode(NodeIndex p) {
  assert (0<= p.getHight() && p.getHight() <= getMaxTreeHight());

  _octree tree;
  Hight h= getExistNode(p, tree);

  NodeIndex idx= p;
  idx.setHight(h);

  if (h > p.getHight() || h == 0) {
    assert(OctStruct::isLeaf(*tree));
  }
  return idx;
}

// ##### getMaxTreeHight() ###########################################
Hight IndexOct::getMaxTreeHight() {
  return rootHight;
}

// ##### getPart() ###################################################
PartType IndexOct::getPart(AxIndex idx, Hight h) {
  return (idx >> h) % AXIS_PARTS;
}

// ##### getPart() 
PartType IndexOct::getPart(NodeIndex p, Hight h) {
  PartType part= 0;
  for (Axis axis= DIMENSIONS - 1; axis >= 0; --axis) {
    part= AXIS_PARTS*part + getPart(p[axis], h);
  }
  assert (part < OCT_PARTS);
  return part;
}

// ##### getPartOfs() ################################################
AxIndex IndexOct::getPartOfs(PartType partNumber, Axis axis) {
  return (partNumber >> axis) % AXIS_PARTS;
}

// ##### isIn() ######################################################
bool IndexOct::isIn(NodeIndex p) {
  if (p.getHight() > getMaxTreeHight()) {
    return false;
  }
  for (Axis axis= 0; axis < DIMENSIONS; ++axis) {
    if (p[axis] < 0 ||
	((p[axis] >> (getMaxTreeHight() - p.getHight())) >= 1) ) {
      return false;
    }
  }
  return true;
}

// ##### isIn() 
bool IndexOct::isIn(NodeIndex p, Hight h) {
  return p.getHight() <= h && h <= getMaxTreeHight() && isIn(p);
}

// ##### isLeaf() ####################################################
bool IndexOct::isLeaf(NodeIndex p) {
  Node* nodePtr;
#ifdef NDEBUG
  getExistNode(p, nodePtr);
#else
  Hight h= getExistNode(p, nodePtr);
  assert (isIn(p, h));
#endif

  return OctStruct::isLeaf(*nodePtr);
}

#ifdef MARK_BORDER
// ##### setBorderColor() ############################################
void IndexOct::setBorderColor(NodeIndex p, Color color) {
  Node* nodePtr;
  getExistNode(p, nodePtr);

  assert (OctStruct::isLeaf(*nodePtr));

  OctStruct::setBorderColor(*nodePtr, color);
}
#endif

// ##### setColor() ##################################################
void IndexOct::setColor(NodeIndex p, Color color) {
  Node* nodePtr;
  getExistNode(p, nodePtr);

  assert (OctStruct::isLeaf(*nodePtr));

  OctStruct::setColor(*nodePtr, color);
}

// EOF: src/octree/index_oct.cpp

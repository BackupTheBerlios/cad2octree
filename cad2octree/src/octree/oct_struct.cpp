/**
 * file: src/octree/oct_struct.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <octree/oct_struct.h>

#include <assert.h>
#include <stdlib.h>

// ##### OctStruct() #################################################
OctStruct::OctStruct() throw (NotEnoughMemoryException*) : countBorderNodes(0) 
{
  root= createOneLeaf();
}

// ##### clear() #####################################################
void OctStruct::clear() {
  assert (exist(getTree()));

  remove(root->parts);
}

// ##### canCompact() ################################################
bool OctStruct::canCompact(Node node, Color &color) {
  if (isLeaf(node)) {
    return false;
  }
  if (!isLeaf(node.parts[0])) {
    return false;
  }
  color= getColor(node.parts[0]);
  for (PartType i= 1; i < OCT_PARTS; i++) {
    if (!isLeaf(node.parts[i])) {
      return false;
    }
    if (color != getColor(node.parts[i])) {
      return false;
    }
  }
  return true;
}

// ##### compact() ###################################################
void OctStruct::compact(Node &node) {
  if (isLeaf(node)) {
    return;
  }
  for (PartType i= 0; i < OCT_PARTS; ++i) {
    compact(node.parts[i]);
  }
  Color color;
  if (canCompact(node, color)) {
    compact(node, color);
  }
}

// ##### compact()
void OctStruct::compact(Node &node, Color color) {
  remove(node.parts);
  setLeaf(node);
  setColor(node, color);
}

// ##### createLeafs() ###############################################
OctStruct::_octree OctStruct::createLeafs() throw (NotEnoughMemoryException*) {
  _octree newParts;
  newParts= (_octree)malloc(getNodeSize());
  if (newParts == NULL) {
    throw new NotEnoughMemoryException();
  }

  for (PartType i= 0; i < OCT_PARTS; ++i) {
    setLeaf(newParts[i]);
#ifdef FILL_SOLIDS
#ifndef CLASSIC_MODE
    newParts[i].flag= UNDEF_OBJ;
#else
    setColor(newParts[i], NO_OBJECT);
#endif
#else
    setColor(newParts[i], NO_OBJECT);
#endif
  }
  return newParts;
}

// ##### createOneLeaf() #############################################
OctStruct::_octree OctStruct::createOneLeaf()
    throw (NotEnoughMemoryException*) {
  _octree newLeaf= (_octree)malloc(getNodeSize());
  if (newLeaf == NULL) {
    throw new NotEnoughMemoryException();
  }

  setLeaf(*newLeaf);
#ifdef FILL_SOLIDS
#ifndef CLASSIC_MODE
  newLeaf->flag= UNDEF_OBJ;
#else
  setColor(*newLeaf, NO_OBJECT);
#endif
#else
  setColor(*newLeaf, NO_OBJECT);
#endif
  return newLeaf;
}

// ##### empty() #####################################################
bool OctStruct::empty() {
  assert (exist(getTree()));

#ifdef AUTOFLUSH
  flush();
#endif
  if (!isLeaf(*getTree())) {
    return false;
  }
  return isNoObject(*getTree());
}

// ##### exist() #####################################################
bool OctStruct::exist(_octree tree) {
  return tree != NULL;
}

// ##### flush() #####################################################
void OctStruct::flush() {
  assert (exist(getTree()));

  compact(*root);
}

#ifdef MARK_BORDER
// ##### getBorderColor() ############################################
Color OctStruct::getBorderColor(Node node) {
  Color flagColor= getColor(node);
  return flagColor + MAX_COLOR + 1;
}
#endif

// ##### getColor() ##################################################
Color OctStruct::getColor(Node node) {
#ifdef AUTOFLUSH
  compact(node);
#endif
  assert (isLeaf(node));

  return node.flag;
}

// ##### getMaxColor() ###############################################
Color OctStruct::getMaxColor() {
  return 1;
}

// ##### getNodeSize() ###############################################
size_t OctStruct::getNodeSize() {
  return sizeof(Node[OCT_PARTS]);
}

// ##### getTree() ###################################################
OctStruct::_octree& OctStruct::getTree() {
  return root;
}

#ifdef MARK_BORDER
// ##### isBorderNode() ##############################################
bool OctStruct::isBorderNode(Node node) {
  return (!isUndefObj(node)) && (node.flag < NO_OBJECT);
}
#endif

// ##### isLeaf() ####################################################
bool OctStruct::isLeaf(Node node) {
  return node.parts == NULL;
}

// ##### isNoObject() ################################################
bool OctStruct::isNoObject(Node node) {
  assert (isLeaf(node));

  return node.flag == NO_OBJECT;
}

// ##### isUndefObj() ################################################
bool OctStruct::isUndefObj(Node node) {
  assert (isLeaf(node));

  return node.flag == UNDEF_OBJ;
}

// ##### getChild() ##################################################
OctStruct::_octree OctStruct::getChild(_octree parent, PartType i) {
  assert (exist(parent));
  assert (!isLeaf(*parent));

  assert (exist(&(parent->parts[i])));
  return &(parent->parts[i]);
}

// ##### print() #####################################################
void OctStruct::print() {
  assert (exist(getTree()));

  cout << "Oktalbaum: ";
  if (empty()) {
    cout << "leer.";
  } else {
    printTree(*getTree());
  }
  cout << endl;
}

// ##### printTree() #################################################
void OctStruct::printTree(Node node) {
  if (isLeaf(node)) {
    cout << '+';
    ( isUndefObj(node) ? cout << '?' : cout << getColor(node) );
    return;
  }

  cout << "(";
  for (PartType i= 0; i < OCT_PARTS; ++i) {
    printTree(node.parts[i]);
  }
  cout << ")";
}

// ##### remove() ####################################################
void OctStruct::remove(_octree &subtree) {
  if (subtree == NULL) {
    return;
  }
  if (!isLeaf(*subtree)) {
    for (PartType i= 0; i < OCT_PARTS; ++i) {
      remove(subtree->parts[i].parts);
    }
  }
  free(subtree);
  subtree= NULL;
}

#ifdef MARK_BORDER
// ##### setBorderColor() ############################################
void OctStruct::setBorderColor(Node &node, Color color) {
  assert (color >= NO_OBJECT);
  assert (isLeaf(node));

  node.flag= color - MAX_COLOR - 1;
}
#endif

// ##### setColor() ##################################################
void OctStruct::setColor(Node &node, Color color) {
  assert (color >= NO_OBJECT);
  assert (isLeaf(node));

  node.flag= color;
}

// ##### setLeaf() ###################################################
void OctStruct::setLeaf(Node &node) {
  node.parts= NULL;
}

// ##### setTree() ###################################################
void OctStruct::setTree(_octree &tree) throw (NotEnoughMemoryException*) {
  if (!exist(tree)) {
    root= createOneLeaf();
  } else {
    root= tree;
  }
}

// ##### stat() ######################################################
void OctStruct::stat(Hight h, unsigned &sumNodes, unsigned &leafs, 
		     unsigned &innerNodes, unsigned &borderNodes, 
		     unsigned &normCells) {
  stat(getTree(), h, sumNodes, leafs, innerNodes, normCells);
  borderNodes= countBorderNodes;
}

// ##### stat() 
void OctStruct::stat(_octree tree, Hight h, 
		     unsigned &sumNodes, unsigned &leafs, 
		     unsigned &innerNodes, unsigned &normCells) {
  if (isLeaf(*tree)) {
    if (getColor(*tree) <= NO_OBJECT) {
      normCells= 0;
    } else {
      normCells= 1 << DIMENSIONS*h;
    }
    sumNodes= 1;
    leafs= 1;
    innerNodes= 0;
    return;
  }

  unsigned countSumNodes= 1;
  unsigned countLeafs= 0;
  unsigned countInnerNodes= 1;
  unsigned countNormCells= 0;

  for (PartType i= 0; i < OCT_PARTS; ++i) {
    stat(getChild(tree, i), h-1, sumNodes, leafs, innerNodes, 
	 normCells);
    countSumNodes+= sumNodes;
    countLeafs+= leafs;
    countInnerNodes+= innerNodes;
    countNormCells+= normCells;
  }

  sumNodes= countSumNodes;
  leafs= countLeafs;
  innerNodes= countInnerNodes;
  normCells= countNormCells;
}

// EOF: src/octree/oct_struct.cpp

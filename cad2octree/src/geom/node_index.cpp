/**
 * file: src/geom/node_index.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <node_index.h>

#include <geom_point.h>
#include <polygon.h>

#include <assert.h>
#include <iostream>

// ##### NodeIndex() #################################################
NodeIndex::NodeIndex(AxIndex x, AxIndex y, AxIndex z, Hight h) {
  assert (DIMENSIONS == 3);

  indices[X_AXIS]= x;
  indices[Y_AXIS]= y;
  indices[Z_AXIS]= z;

  hight= h;
}

// ##### getAxCoordinate() ###########################################
AxIndex NodeIndex::getCoordinate(Axis axis) {
  assert (axis < DIMENSIONS);

  return indices[axis];
}

// ##### getHight() ##################################################
Hight NodeIndex::getHight() {
  return hight;
}

// ##### getX() ######################################################
AxIndex NodeIndex::getX() {
  return getCoordinate(X_AXIS);
}

// ##### getY() ######################################################
AxIndex NodeIndex::getY() {
  return getCoordinate(Y_AXIS);
}

// ##### getZ() ######################################################
AxIndex NodeIndex::getZ() {
  return getCoordinate(Z_AXIS);
}

// ##### print() #####################################################
void NodeIndex::print() {
  cout << "(" << getCoordinate(0);
  for (Axis axis= 1; axis < DIMENSIONS; axis++) {
    cout << "; " << getCoordinate(axis);
  }
  cout << "| " << hight << ")";
}

// ##### set() #######################################################
void NodeIndex::set(AxIndex x, AxIndex y, AxIndex z) {
  assert (DIMENSIONS == 3);

  setX(x);
  setY(y);
  setZ(z);
}

// ##### setCoordinate() #############################################
void NodeIndex::setCoordinate(Axis axis, AxIndex value) {
  assert (axis < DIMENSIONS);

  indices[axis]= value;
}

// ##### setHight() ##################################################
void NodeIndex::setHight(Hight h) {
  if (h < getHight()) {
    // deeper
    Hight dh= getHight() - h;
    set(getX() << dh, getY() << dh, getZ() << dh);
  } else {
    // higher
    Hight dh= h - getHight();
    set(getX() >> dh, getY() >> dh, getZ() >> dh);
  }
  hight= h;
}

// ##### setX() ######################################################
void NodeIndex::setX(AxIndex value) {
  setCoordinate(X_AXIS, value);
}

// ##### setY() ######################################################
void NodeIndex::setY(AxIndex value) {
  setCoordinate(Y_AXIS, value);
}

// ##### setZ() ######################################################
void NodeIndex::setZ(AxIndex value) {
  setCoordinate(Z_AXIS, value);
}

// ##### operator[] ##################################################
AxIndex NodeIndex::operator[](Axis axis) {
  return getCoordinate(axis);
}

// ##### operator== ##################################################
bool operator==(NodeIndex p1, NodeIndex p2) {
  assert (p1.getHight() == p2.getHight());

  for (Axis axis= 0; axis < DIMENSIONS; ++axis) {
    if (p1[axis] != p2[axis]) {
      return false;
    }
  }
  return true;
}

// ##### operator< ###################################################
bool operator<(NodeIndex p1, NodeIndex p2) {
  assert (p1.getHight() == p2.getHight());

  for (Axis axis= 0; axis < DIMENSIONS; ++axis) {
    if (p1[axis] != p2[axis]) {
      return p1[axis] < p2[axis];
    }
  }
  return false;
}

// EOF: src/geom/node_index.cpp

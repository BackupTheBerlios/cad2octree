/**
 * file: src/geom/geom_point.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <geom_point.h>

#include <geom_vec.h>
#include <octree/index_oct.h>

#include <assert.h>
#include <iostream>

// ##### GeomPoint() #################################################
GeomPoint::GeomPoint(Coordinate x, Coordinate y, Coordinate z, Hight h)
    : indexHight(h) {
  set(x, y, z);
}

// ##### GeomPoint() 
GeomPoint::GeomPoint(NodeIndex p) : indexHight(p.getHight()) {
  set(p.getX() + OFS, p.getY() + OFS, p.getZ() + OFS);
}

// ##### ccw() #######################################################
int GeomPoint::ccw(GeomPoint p1, GeomPoint p2, Axis proj) {
  Axis i= (proj + 1) % DIMENSIONS;
  Axis k= (proj + 2) % DIMENSIONS;

  GeomVec lP1= GeomVec(*this, p1);
  GeomVec lP2= GeomVec(*this, p2);
  if (lP1[i]*lP2[k] > lP1[k]*lP2[i]) return +1;
  if (lP1[i]*lP2[k] < lP1[k]*lP2[i]) return -1;

  return 0;
}

// ##### getAxIndex() ################################################
AxIndex GeomPoint::getAxIndex(Axis axis) {
  assert (axis < DIMENSIONS);

  Coordinate coord= coordinates[axis];
  AxIndex axIdx= (AxIndex)coord;

  return axIdx;
}

// ##### getCoordinate() #############################################
Coordinate GeomPoint::getCoordinate(Axis axis) {
  assert (axis < DIMENSIONS);

  return coordinates[axis];
}

// ##### getDup() ####################################################
GeomPoint GeomPoint::getDup() {
  return GeomPoint(getX(), getY(), getZ(), getHight());
}

// ##### getHight() ##################################################
Hight GeomPoint::getHight() {
  return indexHight;
}

// ##### getNodeIndex() ##############################################
NodeIndex GeomPoint::getNodeIndex() {
  return NodeIndex(getAxIndex(X_AXIS), getAxIndex(Y_AXIS), getAxIndex(Z_AXIS), 
                   getHight());
}

// ##### getX() ######################################################
Coordinate GeomPoint::getX() {
  return getCoordinate(X_AXIS);
}

// ##### getY() ######################################################
Coordinate GeomPoint::getY() {
  return getCoordinate(Y_AXIS);
}

// ##### getZ() ######################################################
Coordinate GeomPoint::getZ() {
  return getCoordinate(Z_AXIS);
}

// ##### print() #####################################################
void GeomPoint::print() {
  cout << "(" << getCoordinate(0);
  for (Axis axis= 1; axis < DIMENSIONS; axis++) {
    cout << "; " << getCoordinate(axis);
  }
  cout << ")";
}

// ##### set() #######################################################
void GeomPoint::set(Coordinate x, Coordinate y, Coordinate z) {
  assert (DIMENSIONS == 3);

  setX(x);
  setY(y);
  setZ(z);
}

// ##### setCoordinate() #############################################
void GeomPoint::setCoordinate(Axis axis, Coordinate value) {
  assert (axis < DIMENSIONS);

  coordinates[axis]= value;
}

// ##### setHight() ##################################################
void GeomPoint::setHight(Hight h) {
  Hight oldHight= getHight();
  if (h == oldHight) {
    return;
  }

  Coordinate dh= (Coordinate)(1 << (Hight)ABS(h - oldHight));
  Coordinate ofs= 0.0;
  if (oldHight < h) {
    set((getX() - ofs) / dh + ofs, (getY() - ofs) / dh + ofs, 
        (getZ() - ofs) / dh + ofs);
  } else {
    set(dh * (getX() - ofs) + ofs, dh * (getY() - ofs) + ofs, 
        dh * (getZ() - ofs) + ofs);
  }
  
  indexHight= h;
}

// ##### setX ########################################################
void GeomPoint::setX(Coordinate value) {
  return setCoordinate(X_AXIS, value);
}

// ##### setY ########################################################
void GeomPoint::setY(Coordinate value) {
  return setCoordinate(Y_AXIS, value);
}

// ##### setZ ########################################################
void GeomPoint::setZ(Coordinate value) {
  return setCoordinate(Z_AXIS, value);
}

// ##### operator[] ##################################################
Coordinate GeomPoint::operator[](Axis axis) {
  return getCoordinate(axis);
}

// ##### operator== ##################################################
bool operator==(GeomPoint p1, GeomPoint p2) {
  assert (p1.getHight() == p2.getHight());

  return GeomVec(p1, p2).isNullVec();
}

// EOF: src/geom/geom_point.cpp

/**
 * file: src/cad/objects/point.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <point.h>

#include <assert.h>
#include <iostream>

// ##### Point() #####################################################
Point::Point(Coordinate x, Coordinate y, Coordinate z) {
  assert (DIMENSIONS == 3);

  coordinates[X_AXIS]= x;
  coordinates[Y_AXIS]= y;
  coordinates[Z_AXIS]= z;
}

// ##### getCoordinate() #############################################
Coordinate Point::getCoordinate(Axis axis) {
  assert (axis < DIMENSIONS);

  return coordinates[axis];
}

// ##### getDataPoint() ##############################################
const CadObject::DataType Point::getDataType() {
  return CadObject::POINT;
}

// ##### getDimension() ##############################################
int Point::getDimension() {
  return 0;
}

// ##### getMaxPoint() ###############################################
Point Point::getMaxPoint() {
  return Point(getX(), getY(), getZ());
}

// ##### getMinPoint() ###############################################
Point Point::getMinPoint() {
  return getMaxPoint();
}

// ##### getX() ######################################################
Coordinate Point::getX() {
  return getCoordinate(X_AXIS);
}

// ##### getY() ######################################################
Coordinate Point::getY() {
  return getCoordinate(Y_AXIS);
}

// ##### getZ() ######################################################
Coordinate Point::getZ() {
  return getCoordinate(Z_AXIS);
}

// ##### print() #####################################################
void Point::print() {
  cout << "(" << getCoordinate(0);
  for (Axis axis= 1; axis < DIMENSIONS; axis++) {
    cout << "; " << getCoordinate(axis);
  }
  cout << ")";
}

// ##### set() #######################################################
void Point::set(Coordinate x, Coordinate y, Coordinate z) {
  assert (DIMENSIONS == 3);

  setX(x);
  setY(y);
  setZ(z);
}

// ##### setCoordinate() #############################################
void Point::setCoordinate(Axis axis, Coordinate value) {
  assert (axis < DIMENSIONS);

  coordinates[axis]= value;
}

// ##### setX ########################################################
void Point::setX(Coordinate value) {
  return setCoordinate(X_AXIS, value);
}

// ##### setY ########################################################
void Point::setY(Coordinate value) {
  return setCoordinate(Y_AXIS, value);
}

// ##### setZ ########################################################
void Point::setZ(Coordinate value) {
  return setCoordinate(Z_AXIS, value);
}

// ##### operator[] ##################################################
Coordinate Point::operator[](Axis axis) {
  return getCoordinate(axis);
}

// ##### operator== ##################################################
bool operator==(Point p1, Point p2) {
  for (Axis axis= 0; axis < DIMENSIONS; axis++) {
    if (!EQUIVAL(p1[axis], p2[axis])) {
      return false;
    }
  }
  return true;
}

// ##### operator< ###################################################
bool operator<(Point p1, Point p2) {
  for (Axis axis= 0; axis < DIMENSIONS; axis++) {
    if (p1[axis] < p2[axis]) {
      return true;
    }
    if (p1[axis] > p2[axis]) {
      return false;
    }
  }
  return false;
}

// ##### operator<< ##################################################
bool operator<<(Point p1, Point p2) {
  for (Axis axis= 0; axis < DIMENSIONS; axis++) {
    if ((p1[axis] > p2[axis]) || EQUIVAL(p1[axis], p2[axis])) {
      return false;
    }
  }
  return true;
}

// EOF: src/cad/objects/point.cpp

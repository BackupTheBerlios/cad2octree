/**
 * file: src/cad/objects/quadrilateral.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/objects/quadrilateral.h>

#include <exception.h>

#include <assert.h>
#include <stdlib.h>

// ##### Quadrilateral() #############################################
Quadrilateral::Quadrilateral(Point pA, Point pB, Point pC, Point pD)
    : pointA(pA), pointB(pB), pointC(pC), pointD(pD) {
}

// ##### getCornerCount() ############################################
int Quadrilateral::getCornerCount() {
  return 4;
}

// ##### getDataType() ###############################################
const CadObject::DataType Quadrilateral::getDataType() {
  return CadObject::QUADRILATERAL;
}

// ##### getHiTriangle() #############################################
Triangle* Quadrilateral::getHiTriangle() {
  return new Triangle(pointC, pointD, pointB);
}

// ##### getLowTriangle() ############################################
Triangle* Quadrilateral::getLowTriangle() {
  return new Triangle(pointA, pointB, pointD);
}

// ##### operator[] ##################################################
Point Quadrilateral::operator[](int idx) {
  switch (idx) {
  case 0: return pointA;
  case 1: return pointB;
  case 2: return pointC;
  case 3: return pointD;
  }
  assert (false);
  return NULL_POINT;
}

// EOF: src/cad/objects/quadrilateral.cpp

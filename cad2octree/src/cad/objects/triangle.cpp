/**
 * file: src/cad/objects/triangle.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/objects/triangle.h>

#include <exception.h>

#include <assert.h>
#include <stdlib.h>

// ##### Triangle() ##################################################
Triangle::Triangle(Point pA, Point pB, Point pC)
  : pointA(pA), pointB(pB), pointC(pC) {
}

// ##### getCornerCount() ############################################
int Triangle::getCornerCount() {
  return 3;
}

// ##### getDataType() ###############################################
const CadObject::DataType Triangle::getDataType() {
  return CadObject::TRIANGLE;
}

// ##### operator[] ##################################################
Point Triangle::operator[](int idx) {
  switch (idx) {
  case 0: return pointA;
  case 1: return pointB;
  case 2: return pointC;
  }
  assert (false);
  return NULL_POINT;
}

// EOF: src/cad/objects/triangle.cpp

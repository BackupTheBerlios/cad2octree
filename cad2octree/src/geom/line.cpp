/**
 * file: src/geom/line.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <line.h>

#include <assert.h>
#include <iostream>

// ##### Line() ######################################################
Line::Line(GeomPoint pA, GeomPoint pB) 
    : pointA(pA), pointB(pB) {
  assert (pA.getHight() == pB.getHight());
}

// ##### getCount() ##################################################
int Line::getCount() {
  return 2;
}

// ##### getDirVec() #################################################
GeomVec Line::getDirVec() {
  return GeomVec(getPoint(0), getPoint(1));
}

// ##### getDistVec() ################################################
GeomVec Line::getDistVec(GeomPoint p) {
  return GeomVec(p, getFootpoint(p));
}

// ##### getFootpoint() ##############################################
GeomPoint Line::getFootpoint(GeomPoint p) {
  assert (p.getHight() == getHight());

  GeomVec vAB= getDirVec();
  GeomVec vAP= GeomVec(getPoint(0), p);
  if (vAB.isNullVec()) {
    return getPoint(0);
  }
  GeomPoint q = ((vAP*vAB)/vAB.getSqrLength())*vAB + getPoint(0);

  return q;
}

// ##### getHight() ##################################################
Hight Line::getHight() {
  return getPoint(0).getHight();
}

// ##### getPoint() ##################################################
GeomPoint Line::getPoint(int idx) {
  switch (idx) {
  case 0: return pointA;
  case 1: return pointB;
  default:;
  }
  assert (false);
  return NULL_GEOM_VEC;
}

// ##### isAtLine() ##################################################
bool Line::isAtLine(GeomPoint p) {
  assert (p.getHight() == getHight());
  
  return p == getFootpoint(p);
}

// ##### isEndpoint() ################################################
bool Line::isEndpoint(GeomPoint p) {
  assert (p.getHight() == getHight());

  for (int i= 0; i < getCount(); ++i) {
    if (p == getPoint(i)) {
      return true;
    }
  }
  return false;
}

// ##### isInStretch() ###############################################
bool Line::isInStretch(GeomPoint p) {
  assert (p.getHight() == getHight());

  if (isEndpoint(p)) {
    return true;
  }

  if (!isAtLine(p)) {
    return false;
  }

  Coordinate lAP= GeomVec(getPoint(0), p).getSqrLength();
  Coordinate lBP= GeomVec(getPoint(1), p).getSqrLength();
  Coordinate lAB= GeomVec(getPoint(0), getPoint(1)).getSqrLength();

  return (lAP < lAB) && (lBP < lAB);
}

// ##### print() #####################################################
void Line::print() {
  cout << "[";
  getPoint(0).print();
  for (int i= 1; i < getCount(); ++i) {
    cout << ", ";
    getPoint(i).print();
  }
  cout << "]";
}

// ##### setHight() ##################################################
void Line::setHight(Hight h) {
  for (int i= 0; i < getCount(); ++i) {
    getPoint(i).setHight(h);
  }
}

// ##### operator[] ##################################################
GeomPoint Line::operator[](int idx) {
  return getPoint(idx);
}

// EOF: src/geom/line.cpp

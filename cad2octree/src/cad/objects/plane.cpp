/**
 * file: src/cad/objects/plane.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <plane.h>

#include <point.h>

#include <iostream>

// ##### getMaxPoint() ###############################################
Point Plane::getMaxPoint() {
  Point maxPoint= operator[](0);
  for (int i= 1; i < getCornerCount(); ++i) {
    maxPoint= maxPoint.max(operator[](i));
  }
  return maxPoint;
}

// ##### getMinPoint() ###############################################
Point Plane::getMinPoint() {
  Point minPoint= operator[](0);
  
  for (int i= 1; i < getCornerCount(); ++i) {
    minPoint= minPoint.min(operator[](i));
  }
  return minPoint;
}

// ##### isPlane() ###################################################
bool Plane::isPlane() {
  return true;
}

// ##### print() #####################################################
void Plane::print() {
  cout << "[ ";
  for (int i= 0; i < getCornerCount(); ++i) {
    operator[](i).print();
    cout << " ";
  }
  cout << "]" << endl;
}

// EOF: src/cad/objects/plane.cpp

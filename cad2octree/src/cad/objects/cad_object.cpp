/**
 * file: src/cad/objects/cad_object.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad_object.h>

#include <point.h>

// ##### isPlane() ###################################################
bool CadObject::isPlane() {
  return false;
}

// ##### max() #######################################################
Point CadObject::max(Point p) {
  Point maxPoint= getMaxPoint();
  return Point(MAX(maxPoint.getX(), p.getX()),
	       MAX(maxPoint.getY(), p.getY()),
	       MAX(maxPoint.getZ(), p.getZ()));
}

// ##### min() #######################################################
Point CadObject::min(Point p) {
  Point minPoint= getMinPoint();
  return Point(MIN(minPoint.getX(), p.getX()),
	       MIN(minPoint.getY(), p.getY()),
	       MIN(minPoint.getZ(), p.getZ()));
}

// EOF: src/cad/objects/cad_object.cpp

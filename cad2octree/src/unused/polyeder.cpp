/**
 * file: src/geom/polyeder.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <polyeder.h>

#include <line.h>

// ##### Polyeder() ##################################################
Polyeder::Polyeder() {}

// ##### add() #######################################################
void Polyeder::add(Polygon* t) {
  assert (t != NULL);
  _polyeder.insert(_polyeder.end(), t);
}

// ##### getCount() ##################################################
int Polyeder::getCount() {
  return _polyeder.size();
}

// ##### getPolygon() ################################################
Polygon Polyeder::getPolygon(int idx) {
  return *_polyeder[idx % getCount()];
}

// ##### isin() ######################################################
bool Polyeder::isIn(GeomPoint p) {
  Line testRay = Line(p,
		      GeomPoint(MAX_AX_INDEX, p.getY(), p.getZ(),
				p.getHight()));
  bool retVal= false;
  GeomPoint s= getPolygon(0).getCentre();
  GeomPoint q(0, 0, 0, p.getHight());
  bool colineral;
  
  for (int i= 1; i <= getCount(); ++ i) {
    Polygon t= getPolygon(i);
    if (t.intersect(testRay, q, colineral)) {
      if (p == q) {
	return true;
      }
      if (!colineral) {
	bool isBorderPoint= t.isAtBorder(q);
	if (!isBorderPoint) {
	  retVal= !retVal;
	} else {
	  GeomPoint c= t.getCentre();
	  GeomPoint middle= 0.5*(s + c);
	  Coordinate min= MIN(testRay.getDistVec(s).getSqrLength(),
			      testRay.getDistVec(c).getSqrLength());
	  if (testRay.getDistVec(middle).getSqrLength() < min) {
	    s= c;
	    retVal= !retVal;
	  }
	}
      }
    }
  }
  return retVal;
}

// ##### print() #####################################################
void Polyeder::print() {
  cout << "Polyeder" << endl;
  cout << "--------" << endl;
  for (Iterator it= _polyeder.begin(); it != _polyeder.end(); ++it) {
    (*it)->print();
    cout << endl;
  }
  cout << endl;
}

// ##### operator[] ##################################################
Polygon Polyeder::operator[](int idx) {
  return getPolygon(idx);
}

// EOF: src/geom/polyeder.cpp

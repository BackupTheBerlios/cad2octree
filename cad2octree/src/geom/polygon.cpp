/**
 * file: src/geom/polygon.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <polygon.h>

#include <assert.h>
#include <iostream>
#include <math.h>

// ##### Polygon() ###################################################
Polygon::Polygon(GeomPoint pA, GeomPoint pB, GeomPoint pC) 
    : cornerCount(3), pointA(pA), pointB(pB), pointC(pC), pointD(pC) {
  assert (pA.getHight() == pB.getHight() && pB.getHight() == pC.getHight());
}

// ##### Polygon() ###################################################
Polygon::Polygon(GeomPoint pA, GeomPoint pB, GeomPoint pC, GeomPoint pD) 
    : cornerCount(4), pointA(pA), pointB(pB), pointC(pC), pointD(pD) {
  assert (Polygon(pA, pB, pC).isInPlane(pD));
}

// ##### getCount() ##################################################
int Polygon::getCount() {
  return cornerCount;
}

// ##### getDup() ####################################################
Polygon Polygon::getDup() {
  if (getCount() == 3) {
    return Polygon(pointA.getDup(), pointB.getDup(), pointC.getDup());
  }
  return Polygon(pointA.getDup(), pointB.getDup(),
		 pointC.getDup(), pointD.getDup());
}

// ##### getFootpoint() ##############################################
GeomPoint Polygon::getFootpoint(GeomPoint p) {
  assert (p.getHight() == getHight());

  GeomVec vn= getNormVec();
  assert (vn.getHight() == p.getHight());
  Coordinate d= vn*getPoint(0);
  return p - (vn*p-d)*vn;
}

// ##### getHight() ##################################################
Hight Polygon::getHight() {
  return getPoint(0).getHight();
}

// ##### getNormVec() ################################################
GeomVec Polygon::getNormVec() {
  GeomVec vAB= GeomVec(getPoint(0), getPoint(1));
  GeomVec vAC= GeomVec(getPoint(0), getPoint(2));

  return vAB.vec_prod(vAC).getNormalize();
}

// ##### getPoint() ##################################################
GeomPoint& Polygon::getPoint(int idx) {
  assert (idx < getCount());
  switch (idx) {
  case 0: return pointA;
  case 1: return pointB;
  case 2: return pointC;
  case 3: return pointD;
  default:;
  }
  assert (false);
  return pointA;
}

// ##### isAtBorder() ################################################
bool Polygon::isAtBorder(GeomPoint p) {
  assert (p.getHight() == getHight());

  for (int i= 0; i < getCount(); ++i) {
    if (Line(getPoint(i), getPoint((i+1) % getCount())).isInStretch(p)) {
      return true;
    }
  }
  return false;
}

// ##### isCorner() ##################################################
bool Polygon::isCorner(GeomPoint p) {
  assert (p.getHight() == getHight());

  for (int i= 0; i < getCount(); ++i) {
    if (p == getPoint(i)) {
      return true;
    }
  }
  return false;
}

// ##### isIn() ######################################################
bool Polygon::isIn(GeomPoint p) {
  Polygon _dup= getDup();

  _dup.setHight(p.getHight());
  assert (p.getHight() == _dup.getHight());

  if (_dup.isCorner(p)) {
    return true;
  }
  if (!_dup.isInPlane(p)) {
    return false;
  }
  if (_dup.isAtBorder(p)) {
    return true;
  }

#ifdef CCW_CHECK
  assert (getCount() == 3);
  // p und Polygon werden in die xy-, xz- oder yz-Ebene projeziert
  // Als Projektionsebene wird die Ebene gewählt, in der das Polygon nicht 
  // entartet als Punkt oder Strecke dargestellt wird
  // Geht das nicht, so war das Polygon ansich schon entartet. Da p
  // nicht auf dem Polygonrand lag (s.o.), muss p außerhalb des Polygons 
  // liegen.
  // Für die 'normalen' Fälle kann nun der ccw-Test verwendet werden.
  bool noPolygon= false;
  Axis proj= 0;
  GeomPoint pA= _dup.getPoint(0);
  GeomPoint pB= _dup.getPoint(1);
  GeomPoint pC= _dup.getPoint(2);
  for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
    if (pA[ax] == pB[ax] && pA[ax] == pC[ax]) {
      if (noPolygon) {
        return false;
      } else {
        noPolygon= true;
	proj= ax;
      }
    }
  }
  return _dup.isIn(p, proj);
#else
  // p liegt nur dann innerhalb des Dreiecks, wenn er für alle
  // Dreiecksseiten gilt:
  // Die Winkelsumme über die Winkel an p zu den jeweiligen
  // Dreiecksseitenendpunkten ergibt 2*PI (Sonderfälle sind oben
  // behandelt)
  GeomPoint q= _dup.getFootpoint(p);
  Coordinate angle= 0.0;
  for (int i= 0; i < getCount(); ++i) {
    GeomVec lQA= GeomVec(q, _dup.getPoint(i));
    GeomVec lQB= GeomVec(q, _dup.getPoint((i+1) % getCount()));
    angle= angle + lQA.getAngle(lQB);
  }
  return EQUIVAL(angle, 2.0*M_PI);
#endif
}

// ##### isIn() 
bool Polygon::isIn(GeomPoint q, Axis proj) {
  assert (GeomVec(q, getFootpoint(q)).isNullVec());

  // Liegt q innerhalb des Dreiecks (Rand inklusive) ?
  int polygonCcw= getPoint(0).ccw(getPoint(1), getPoint(2), proj);
  for (int i= 0; i < getCount(); ++i) {
    int k= (i+1) % getCount();
    int qCcw= q.ccw(getPoint(i), getPoint(k), proj);
    int rotDir= polygonCcw * qCcw;

    if (rotDir == 0) {
      Coordinate l= GeomVec(getPoint(i), getPoint(k)).getSqrLength();
      if ( (l <= GeomVec(getPoint(i), q).getSqrLength()) 
	   || (l <= GeomVec(q, getPoint(k)).getSqrLength()) ) {
	return false;
      }
    } 
    else  if (rotDir < 0) {
      return false;
    }
  }
  return true;
}

// ##### isInPlane() #################################################
bool Polygon::isInPlane(GeomPoint p) {
  assert (p.getHight() == getHight());

#ifndef ALGORITHM_CHECK_DET
  return p == getFootpoint(p);
#else
  GeomVec nAB= GeomVec(getPoint(0), getPoint(1));
  GeomVec nAC= GeomVec(getPoint(0), getPoint(2));
  GeomVec lineAP= GeomVec(getPoint(0), p);

  Coordinate det= GeomVec::det(nAB, nAC, lineAP);
  Coordinate areaABC= nAB.vec_prod(nAC).getSqrLength();

  return det*det < DET_MAX * areaABC;
#endif
}

// ##### print() #####################################################
void Polygon::print() {
  cout << "[";
  getPoint(0).print();
  for (int i= 1; i < getCount(); ++i) {
    cout << ", ";
    getPoint(i).print();
  }
  cout << "]";
}

// ##### setHight() ##################################################
void Polygon::setHight(Hight h) {
  for (int i= 0; i < getCount(); ++i) {
    getPoint(i).setHight(h);
  }
}

// ##### testLine() ##################################################
bool Polygon::testLine(GeomPoint p, GeomPoint &q, 
		       bool &intersect, bool &inside) {
  assert (p.getHight() == getHight());

  Axis ax= RAY_AXIS;
  GeomPoint pA= getPoint(0);
  GeomVec nVec= getNormVec();
  Coordinate divisor= nVec[ax];

  if (EQUIVAL(divisor, 0.0)) {
    inside= false;
    intersect= false;
    return false;
  }
  
  
  q= p;
  Coordinate t= (GeomVec(pA, p) * nVec) / divisor;
  q.setCoordinate(ax, p[ax] - t);
  
  inside= ((q[ax] - p[ax]) * nVec[ax] >= 0);
  intersect= isIn(q, ax);

  return true;
}

// ##### operator[] ##################################################
GeomVec Polygon::operator[](int idx) {
  return getPoint(idx);
}

// EOF: src/geom/polygon.cpp

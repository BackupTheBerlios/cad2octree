/**
 * file: src/geom/geom_vec.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <geom_vec.h>
#include <global.h>

#include <math.h>
#include <assert.h>
#include <iostream>

// ##### GeomVec() ###################################################
GeomVec::GeomVec(GeomPoint p) : GeomPoint(p) {}

// ##### GeomVec() 
GeomVec::GeomVec(GeomVec pStart, GeomVec pEnd) : GeomPoint(pEnd - pStart) {
  assert (pStart.getHight() == pEnd.getHight());
}

// ##### det() #######################################################
Coordinate GeomVec::det(GeomVec a, GeomVec b, GeomVec c) {
  assert (a.getHight() == b.getHight() && b.getHight() == c.getHight());

  // | a_x b_x c_x | a_x  b_x
  // | a_y b_y c_y | a_y  b_y
  // | a_z b_z c_z | a_z  b_z
  return a[X_AXIS] * (b[Y_AXIS]*c[Z_AXIS] - c[Y_AXIS]*b[Z_AXIS])
    + b[X_AXIS] * (c[Y_AXIS]*a[Z_AXIS] - a[Y_AXIS]*c[Z_AXIS])
    + c[X_AXIS] * (a[Y_AXIS]*b[Z_AXIS] - b[Y_AXIS]*a[Z_AXIS]);
}

// ##### getAngle() ##################################################
Coordinate GeomVec::getAngle(GeomVec v) {
  assert (v.getHight() == getHight());

  return acos(getNormalize()*v.getNormalize());
}

// ##### getNormalize() ##############################################
GeomVec GeomVec::getNormalize() {
  Coordinate length= sqrt(getSqrLength());
  if (EQUIVAL(length, 0.0)) {
    GeomVec v= NULL_GEOM_VEC;
    v.setHight(getHight());
    return v;
  }
  return (1.0/length) * (*this);
}

// ##### getSqrLength() ##############################################
Coordinate GeomVec::getSqrLength() {
  return (*this) * (*this);
}

// ##### isNullVec() ################################################
bool GeomVec::isNullVec() {
  return ABS(getSqrLength()) < VEC_ABS_MAX + EPSILON;
}

// ##### vec_prod() ##################################################
GeomVec GeomVec::vec_prod(GeomVec v) {
  assert (v.getHight() == getHight());
  // | e_x e_y e_z |
  // | t_x t_y t_z |
  // | v_x v_y v_z |

  return GeomPoint(getY()*v[Z_AXIS] - getZ()*v[Y_AXIS],
		   getZ()*v[X_AXIS] - getX()*v[Z_AXIS], 
		   getX()*v[Y_AXIS] - getY()*v[X_AXIS], 
		   getHight());
}

// ##### operator- ###################################################
GeomVec GeomVec::operator-() {
  return GeomPoint(-getX(), -getY(), -getZ(), getHight());
}

// ##### operator- 
GeomVec operator-(GeomVec p1, GeomVec p2) {
  return p1 + (-p2);
}

// ##### operator+ ###################################################
GeomVec operator+(GeomVec p1, GeomVec p2) {
  assert (p1.getHight() == p2.getHight());

  return GeomPoint
    ( p1.getX() + p2.getX(), p1.getY() + p2.getY(), p1.getZ() + p2.getZ(),
      p1.getHight() );
}

// ##### operator* ###################################################
GeomVec operator*(double r, GeomVec p) {
  return GeomPoint(r*p.getX(), r*p.getY(), r*p.getZ(), p.getHight());
}

// ##### operator* ###################################################
Coordinate operator*(GeomVec p1, GeomVec p2) {
  assert (p1.getHight() == p2.getHight());

  return p1.getX()*p2.getX() + p1.getY()*p2.getY() + p1.getZ()*p2.getZ();
}

// EOF: src/geom/geom_vec.cpp

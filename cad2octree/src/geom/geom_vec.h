/**
 * @file src/geom/geom_vec.h
 * Definiert Vektoren zwischen geometrischen Punkten GeomPoint.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __GEOM_VEC_H__
#define __GEOM_VEC_H__

#include <geom_point.h>

#include <node_vec.h>

/**
 * 0-Vektor.
 */
#define NULL_GEOM_VEC GeomPoint(0, 0, 0)

/**
 * Definiert Vektoren zwischen geometrischen Punkten.
 *
 * Hierfür wird GeomPoint um weitere Operationen erweitert.
 */
class GeomVec : public GeomPoint {
 public:
  /**
   * Default-Konstruktor.
   * Erzeugt den GeomVec zum GeomPoint p.
   * @param p geometrischer Punkt
   */
  GeomVec(GeomPoint p);

  /**
   * Konstruktor.
   * Erzeugt den GeomVec, der den Vektor
   * \f$\over{\mbox{pStart}\ \mbox{pEnd}}\f$ darstellt.
   * @param pStart Quelle
   * @param pEnd Ziel
   * @pre pStart.getHight() == pEnd.getHight()
   */
  GeomVec(GeomVec pStart, GeomVec pEnd);

  /**
   * Liefert die Determinante aus den Vektoren a, b und c.
   * @param a erster Vektor
   * @param b zweiter Vektor
   * @param c dritter Vektor
   * @return die Determinante det(a, b, c)
   * @pre a.getHight() = b.getHight() = c.getHight()
   */
  static Coordinate det(GeomVec a, GeomVec b, GeomVec c);

  /**
   * Liefert den von diesem Vektor und v eingeschlossenen Winkel.
   * Der zurückgegebene Winkel liegt zwischen [0; PI].
   * @param v zweiter Vektor
   * @return Winkel in Radiant
   * @pre v.getHight() = getHight()
   */
  Coordinate getAngle(GeomVec v);

  /**
   * Liefert den zugehöigen normalisierten Vektor, falls der Vektor
   * kein Nullvektor ist. Ist der Vektor der Nullvektor wird ein Nullvektor
   * zurückgeliefert.
   * @return NULL_GEOM_VEC,            falls isNullVec()\n
   *         *this/sqrt(getSqrLength), sonst
   */
  GeomVec getNormalize();

  /**
   * Liefert das Quadrat der 2-Norm des Vektors.
   * @return \f$ \sum_{i= 0}^{\dim - 1} \mbox{getCoordinate(i)}^2 \f$
   */
  Coordinate getSqrLength();

  /**
   * Ist dies ein Nullvektor?
   * @return ABS(getSqrLength()) < SQR_EPSILON
   */
  bool isNullVec();

  /**
   * Liefert das Kreuzprodukt mit v
   * @param v zweiter Vektor
   * @return CROSS_PRODUCT(*this, v)
   * @pre v.getHight() = getHight()
   */
  GeomVec vec_prod(GeomVec v);

  /**
   * Liefert einen geometrischen Vektor der zusammen mit diesem Vektor
   * (additativ) den Nullvektor ergibt.
   * @return NULL_GEOM_VEC - (*this)
   */
  GeomVec operator -();
};

/**
 * Liefert den resultierenden Differenzvektor.
 * @param p1 erster Vektor
 * @param p2 zweiter Vektor
 * @return p1-p2
 * @pre p1.getHight() = p2.getHight()
 */
GeomVec operator-(GeomVec p1, GeomVec p2);

/**
 * Liefert den resultierenden Summenvektor.
 * @param p1 erster Vektor
 * @param p2 zweiter Vektor
 * @return p1+p2
 * @pre p1.getHight() = p2.getHight()
 */
GeomVec operator+(GeomVec p1, GeomVec p2);

/**
 * Liefert um r gestreckten p.
 * @param r Streckfaktor
 * @param p Knotenvektor
 * @return r*p
 */
GeomVec operator*(double r, GeomVec p);

/**
 * Liefert das Skalarprodukt aus p1 und p2.
 * @param p1 erster Vektor
 * @param p2 zweiter Vektor
 * @return <p1; p2>
 * @pre p1.getHight() = p2.getHight()
 */
Coordinate operator*(GeomVec p1, GeomVec p2);

#endif // ! __GEOM_VEC_H__

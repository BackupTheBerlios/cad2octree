/**
 * @file src/cad/objects/triangle.h
 * Definiert den Dreieck-Typ Triangle.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <plane.h>
#include <point.h>

/**
 * Konkrete Klasse für ein Dreieck.
 */
class Triangle : public Plane {
 public:
  /**
   * Konstruktor.
   * @param pA erster Eckpunkt
   * @param pB zweiter Eckpunkt
   * @param pC dritter Eckpunkt
   */
  Triangle(Point pA, Point pB, Point pC);

  /**
   * Liefert die Anzahl der Eckpunkte.
   * @return 3
   */
  virtual int getCornerCount();

  /**
   * Liefert die Art des CAD-Objekts zurück.
   * @return CadObject::TRIANGLE
   */
  virtual const DataType getDataType();

  /**
   * Liefert den idx-ten Eckpunkt.
   * @param idx wievielter Eckpunkt
   * @return Eckpunkt Nr. idx
   * @pre 0 <= idx < 3
   */
  Point operator[](int idx);

 private:
  /**
   * Eckpunkt A
   */
  Point pointA;

  /**
   * Eckpunkt B
   */
  Point pointB;

  /**
   * Eckpunkt C
   */
  Point pointC;
}; // class Triangle

#endif // ! __TRIANGLE_H__

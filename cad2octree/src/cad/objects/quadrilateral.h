/**
 * @file src/cad/objects/quadrilateral.h
 * Definiert den Viereck-Typ Quadrilateral.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __QUADRILATERAL_H__
#define __QUADRILATERAL_H__

#include <plane.h>
#include <point.h>
#include <triangle.h>

/**
 * Konkrete Klasse für ein Viereck.
 */
class Quadrilateral : public Plane {
 public:
  /**
   * Konstruktor.
   * @param pA erster Eckpunkt
   * @param pB zweiter Eckpunkt
   * @param pC dritter Eckpunkt
   * @param pD vierter Eckpunkt
   */
  Quadrilateral(Point pA, Point pB, Point pC, Point pD);

  /**
   * Liefert die Anzahl der Eckpunkte.
   * @return 4
   */
  virtual int getCornerCount();

  /**
   * Liefert die Art des CAD-Objekts zurück.
   * @return CadObject::QUADRILATERAL
   */
  virtual const DataType getDataType();

  /**
   * Liefert das Dreieck CDB
   * @return Dreieck CDB
   */
  Triangle* getHiTriangle();

  /**
   * Liefert das Dreieck ABD
   * @return Dreieck ABD
   */
  Triangle* getLowTriangle();

  /**
   * Liefert den idx-ten Eckpunkt.
   * @param idx wievielter Eckpunkt
   * @return Eckpunkt Nr. idx
   * @pre 0 <= idx < 4
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

  /**
   * Eckpunkt D
   */
  Point pointD;
}; // class Quadrilateral

#endif // ! __QUADRILATERAL_H__

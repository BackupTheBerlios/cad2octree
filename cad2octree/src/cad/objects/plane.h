/**
 * @file src/cad/objects/plane.h
 * Definiert eine allgemeine abstrakte ebene Fl�che.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __PLANE_H__
#define __PLANE_H__

#include <face.h>

/**
 * Allgemeine Klasse f�r \em ebene Fl�chen.
 */
class Plane : public Face {
 public:
  /**
   * Liefert die Anzahl der begrenzenden Eckpunkte.
   * @return Eckpunktanzahl
   */
  virtual int getCornerCount()= 0;

  /**
   * Liefert den Punkt zur�ck, der jeweils das Maximum aller
   * Eckpunktkoordinaten enth�lt.
   * @return vorderer oberer rechter Punkt des ebenen Fl�chenobjekts
   *         umschlie�enden Quaders
   */
  virtual Point getMaxPoint();

  /**
   * Liefert den Punkt zur�ck, der jeweils das Minimum aller
   * Eckpunktkoordinaten enth�lt.
   * @return hinterer unterer linker Punkt des ebenen Fl�chenobjekts
   *         umschlie�enden Quaders
   */
  virtual Point getMinPoint();

  /**
   * Ist das Objekt eben?
   * @return true
   */
  virtual bool isPlane();

  /**
   * Gibt die Begrenzungspunkte auf der Konsole aus.
   */
  virtual void print();

  /**
   * Liefert den idx-ten Eckpunkt
   * @param idx wievielter Eckpunkt
   * @return Eckpunkt Nr. idx
   */
  virtual Point operator[](int idx)= 0;

};

#endif // ! __PLANE_H__

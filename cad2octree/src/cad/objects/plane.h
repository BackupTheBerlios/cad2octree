/**
 * @file src/cad/objects/plane.h
 * Definiert eine allgemeine abstrakte ebene Fläche.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __PLANE_H__
#define __PLANE_H__

#include <face.h>

/**
 * Allgemeine Klasse für \em ebene Flächen.
 */
class Plane : public Face {
 public:
  /**
   * Liefert die Anzahl der begrenzenden Eckpunkte.
   * @return Eckpunktanzahl
   */
  virtual int getCornerCount()= 0;

  /**
   * Liefert den Punkt zurück, der jeweils das Maximum aller
   * Eckpunktkoordinaten enthält.
   * @return vorderer oberer rechter Punkt des ebenen Flächenobjekts
   *         umschließenden Quaders
   */
  virtual Point getMaxPoint();

  /**
   * Liefert den Punkt zurück, der jeweils das Minimum aller
   * Eckpunktkoordinaten enthält.
   * @return hinterer unterer linker Punkt des ebenen Flächenobjekts
   *         umschließenden Quaders
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

/**
 * @file src/geom/polyeder.h
 * Definiert einen Polyeder aus Dreiecken.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __POLYEDER_H__
#define __POLYEDER_H__

#include <polygon.h>

#include <vector>

/**
 * Polyeder aus Dreiecken.
 */
class Polyeder {
 public:
  /**
   * Default-Konstruktor.
   */
  Polyeder();

  /**
   * Fügt das Polygon t zum Polyeder hinzu.
   * @param t hinzuzufügendes Polygon
   * @pre t != NULL
   */
  void add(Polygon *t);

  /**
   * Liefert die Anzahl der Polygone des Polyeders
   * @param Anzahl der Polygone
   */
  int getCount();

  /**
   * Liefert das Polygon mit dem Index idx.
   * @param idx Index-Nummer
   * @return Polygon mit Index idx mod getCount()
   */
  Polygon getPolygon(int idx);

  /**
   * Befindet sich p in diesem Polyeder?
   * @param p Testpunkt
   * @return Ob sich p in diesem Polyeder befindet.
   */
  bool isIn(GeomPoint p);

  /**
   * Gibt die Knotenidizes des Polygonzugs auf der Konsole aus.
   */
  void print();

  /**
   * Liefert das Dreieck mit dem Index idx.
   * @param idx Index-Nummer
   * @return Dreieck mit Index idx mod getCount()
   */
  Polygon operator[](int idx);

 private:
  /**
   * Cursortyp zum Iterieren über die Polygone des Polyeders
   */
  typedef vector<Polygon *>::iterator Iterator;

  /**
   * Die Polygone des Polyeders
   */
  vector<Polygon *> _polyeder;
};

#endif // ! __POLYEDER_H__

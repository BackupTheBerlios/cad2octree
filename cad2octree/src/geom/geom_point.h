/**
 * @file src/geom/geom_point.h
 * Bildet den NodeIndex im (R,R,R) ab.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __GEOM_POINT_H__
#define __GEOM_POINT_H__

#include <global.h>
#include <node_index.h>

/**
 * Verschiebung zum Zellmittelpunkt
 */
static const Coordinate OFS= 0.5;

/**
 * Bildet den NodeIndex im (R,R,R) ab.
 */
class GeomPoint {
 public:
  /**
   * Default-Konstruktor.
   * @param x x-Koordinate
   * @param y y-Koordinate
   * @param z z-Koordinate
   * @param h Höhe des zugehörigen Knotenindex in der Oktalbaumstruktur
   * @pre DIMENSIONS = 3
   */
  GeomPoint(Coordinate x, Coordinate y, Coordinate z,
	    Hight h= BASE_NODE_HIGHT);

  /**
   * Konstruktor.
   * @param p NodeIndex
   */
  GeomPoint(NodeIndex p);

  /**
   * Liefert den Umlaufsinn der die Projektion in die Ebene (proj) = t 
   * dieses Punkts mit den Punkten p1 und p2 besitzt.
   * @param p1 Punkt 1
   * @param p2 Punkt 2
   * @param proj Achse, die senkrecht auf der Projektionsebene steht
   * @return \b 0, falls dieser Punkt mit den Punkten p1 und p2 kein 'echtes' 
   *               Dreieck bilen (also nur Strecke oder Punkt) \n
   *         \b 1, Punkte liegen im Gegenuhrzeigersinn
   *	     \b -1, Punkte liegen im Uhrzeigersinn
   */
  int ccw(GeomPoint p1, GeomPoint p2, Axis proj);

  /**
   * Liefert den zur Koordinate getCoordinate(axis) zugehörgen AxIndex. 
   * Es gilt für ein reguläres Objekt p
   * vom Typ NodeIndex: p[axis] == GeomPoint(p).getAxIndex(axis)
   * @return AxIndex der Koordinate getCoordinate(axis)
   */
  AxIndex getAxIndex(Axis axis);

  /**
   * Liefert die Koordinate der Achse axis.
   * @param axis Koordinaten-Achse
   * @return Koordinate der Achse
   * @pre axis < DIMENSIONS
   */
  Coordinate getCoordinate(Axis axis);

  /**
   * Liefert eine Kopie des geometrischen Punktes.
   * @return Kopie
   */
  GeomPoint getDup();

  /**
   * Liefert die Höhe des zugehörigen Knotenindex in der Oktalbaumstruktur.
   * @return Punkthöhe
   */
  Hight getHight();

  /**
   * Liefert den zugehörgen Knotenindex. Es gilt für ein reguläres Objekt p
   * vom Typ NodeIndex: p == GeomPoint(p).getNodeIndex()
   * @return Knotenindex
   */
  NodeIndex getNodeIndex();

  /**
   * Liefert die x-Koordinate.
   * @return x-Koordinate
   */
  Coordinate getX();

  /**
   * Liefert die y-Koordinate.
   * @return y-Koordinate
   */
  Coordinate getY();

  /**
   * Liefert die z-Koordinate.
   * @return z-Koordinate
   */
  Coordinate getZ();

  /**
   * Gibt die Punktkoordinaten auf der Konsole aus.
   */
  virtual void print();

  /**
   * Setzt die Koordinaten des Punktes.
   * @param x neuer Wert der x-Koordinate
   * @param y neuer Wert der y-Koordinate
   * @param z neuer Wert der z-Koordinate
   * @pre DIMENSIONS = 3
   */
  void set(Coordinate x, Coordinate y, Coordinate z);

  /**
   * Setzt die Koordinate der Koordinatenachse axis auf den Wert value.
   * @param axis Koordinatenachse
   * @param value neuer Wert
   * @pre axis < DIMENSIONS
   */
  void setCoordinate(Axis axis, Coordinate value);

  /**
   * Setzt die Höhe des zugehörigen Knotenindex in der Oktalbaumstruktur.
   * @param h Punkthöhe
   */
  void setHight(Hight h);

  /**
   * Setzt die Koordinate der x-Achse auf den Wert value.
   * @param value neuer Wert
   */
  void setX(Coordinate value);

  /**
   * Setzt die Koordinate der y-Achse auf den Wert value.
   * @param value neuer Wert
   */
  void setY(Coordinate value);

  /**
   * Setzt die Koordinate der z-Achse auf den Wert value.
   * @param value neuer Wert
   */
  void setZ(Coordinate value);

  /**
   * Equivalent zu getCoordinate(axis).
   * @return Koordinate der Achse axis
   */
  Coordinate operator[](Axis axis);

 private:
  /**
   * Koordinaten des Punktes
   */
  Coordinate coordinates[DIMENSIONS];

  /**
   * Höhe des zugehörigen NodeIndex.
   */
  Hight indexHight; 
}; // class GeomPoint

// ##### zugehörige Vergleichsoperatoren #############################

/**
 * Sind alle Koordinaten der Punkte p1 und p2 paarweise identisch?
 * @param p1 erster Punkt
 * @param p2 zweiter Punkt
 * @return \f$\forall axis \in [0;\dim) :
 *               p1[axis] = p2[axis] \f$
 * @pre p1.getHight() = p2.getHight()
 */
bool operator==(GeomPoint p1, GeomPoint p2);

#endif // ! __GEOM_POINT_H__

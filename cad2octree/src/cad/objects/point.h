/**
 * @file src/cad/objects/point.h
 * Definiert den Punkt-Typ Point.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <global.h>
#include <cad_object.h>

#include <math.h>
#include <values.h>

/**
 * Ursprungspunkt
 */
#define NULL_POINT Point(0, 0, 0)

/**
 * 'größter' darstellbarer Punkt
 */
#define MAXIMUM_POSSIBLE_POINT Point(MAXFLOAT, MAXFLOAT, MAXFLOAT)

/**
 * 'kleinster' darstellbarer Punkt
 */
#define MINIMUM_POSSIBLE_POINT Point(-MAXFLOAT, -MAXFLOAT, -MAXFLOAT)

/**
 * Konkrete Klasse für ein Punkt.
 */
class Point : public CadObject {
 public:
  /**
   * Konstruktor.
   * @param x x-Koordinate
   * @param y y-Koordinate
   * @param z z-Koordinate
   * @pre DIMENSIONS = 3
   */
  Point(Coordinate x, //= (Coordinate)0, 
	Coordinate y, //= (Coordinate)0, 
	Coordinate z); //= (Coordinate)0);

  /**
   * Liefert die Koordinate der Achse axis.
   * @param axis Koordinaten-Achse
   * @return Koordinate der Achse
   * @pre axis < DIMENSIONS
   */
  Coordinate getCoordinate(Axis axis);

  /**
   * Liefert die Art des CAD-Objekts zurück.
   * @return CadObject::POINT
   */
  virtual const DataType getDataType();

  /**
   * Liefert zurück, wieviele Dimensionen der Punkt besitzt.
   * @return 0
   */
  virtual int getDimension();

  /**
   * Liefert den Punkt zurück.
   * @return der Punkt
   */
  virtual Point getMaxPoint();

 /**
   * Liefert den Punkt zurück.
   * @return der Punkt
   */
  virtual Point getMinPoint();

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
}; // class Point

// ##### zugehörige Vergleichsoperatoren #############################

/**
 * Sind alle Koordinaten der Punkte p1 und p2 paarweise identisch?
 * @param p1 erster Punkt
 * @param p2 zweiter Punkt
 * @return \f$\forall axis \in [0;\dim) :
 *               p1[axis] = p2[axis] \f$
 */
bool operator==(Point p1, Point p2);

/**
 * Liegt der Punkt p1 'lexikographisch' vor dem Punkt p2?
 * @param p1 erster Punkt
 * @param p2 zweiter Punkt
 * @return \f$\exists \{ axis \in [0;\dim)~ \forall a \in [0;axis) |
 *                         p1[a] = p2[a] 
 *                           \land p1[axis] < p2[axis] \} \f$
 */
bool operator<(Point p1, Point p2);

/**
 * Sind alle Koordinaten des Punktes p1 < als die das Punktes p2?
 * @param p1 erster Punkt
 * @param p2 zweiter Punkt
 * @return \f$\forall axis \in [0;\dim) :
 *               p1[axis] < p2[axis] \f$
 */
bool operator<<(Point p1, Point p2);

#endif // ! __POINT_H__

/**
 * @file src/geom/node_index.h
 * Definiert einen Index f�r die Knoten die in einer OctStruct enthalten sind.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __NODE_INDEX_H__
#define __NODE_INDEX_H__

#include <global.h>

/**
 * H�he eines Blattknotens der untersten Ebene
 */
#define BASE_NODE_HIGHT 0

/**
 * Index-Typ. F�r Raster in eine Achsenrichtung.
 */
typedef int AxIndex;

/**
 * H�chster Wert f�r Index-Typ.
 */
#define MAX_AX_INDEX INT_MAX

/**
 * Richtungstyp f�r eine Koordinatenachse.
 */
typedef int AxDirection;

/**
 * Vorw�rts-Richtung.
 */
const AxDirection BACKWARD= -1;

/**
 * R�chw�rts-Richtung.
 */
const AxDirection FORWARD= +1;

class NodeVec;

/**
 * Klasse f�r den Index f�r Oktalbaumknoten.
 *
 * F�r jede Dimension ist ein ganzzahliger Index definiert.
 * Der Indexbereich ergibt sich aus der 'H�he' hight zu
 * \f$ [0; 2^{\mbox{hight}}-1] \f$.
 *
 * NodeIndex wird von OctStruct verwendet. hight gibt hier die H�he
 * des Punktes in der Oktalbaumstruktur. Die Indizies in alle Raumrichtungen
 * bilden den Punkt eindeutig in einem Octreesegment ab. F�r einen zu
 * betrachtenden 'indizierten Punkt' der Oktalbaumstruktur ist
 * der Unterschied des Index zum Nachbar = 1.
 */
class NodeIndex {
 public:
  /**
   * Konstruktor.
   * @param x x-Index
   * @param y y-Index
   * @param z z-Index
   * @param h H�he des Punktes in der Oktalbaumstruktur
   * @pre DIMENSIONS = 3
   */
  NodeIndex(AxIndex x, AxIndex y, AxIndex z, Hight h= BASE_NODE_HIGHT);

  /**
   * Liefert den Index in Richtunng der Achse axis.
   * @param axis Index-Achse
   * @return Index der Achse
   * @pre axis < DIMENSIONS
   */
  AxIndex getCoordinate(Axis axis);

  /**
   * Liefert die H�he des Punktes in der Oktalbaumstruktur.
   * @return Punkth�he
   */
  Hight getHight();

  /**
   * Liefert den Index in x-Richtung.
   * @return x-Index
   */
  AxIndex getX();

  /**
   * Liefert den Index in y-Richtung.
   * @return y-Index
   */
  AxIndex getY();

  /**
   * Liefert den Index in z-Richtung.
   * @return z-Index
   */
  AxIndex getZ();

  /**
   * Gibt die Punkt-Indizes und seine H�he auf der Konsole aus.
   */
  virtual void print();

  /**
   * Setzt die Indizes des Punktes.
   * @param x neuer x-Index
   * @param y neuer y-Index
   * @param z neuer z-Index
   * @pre DIMENSIONS = 3
   */
  void set(AxIndex x, AxIndex y, AxIndex z);

  /**
   * Setzt den Index in Richtung der Achse axis auf den Wert value.
   * @param axis Index-Achse
   * @param value neuer Wert
   * @pre axis < DIMENSIONS
   */
  void setCoordinate(Axis axis, AxIndex value);

  /**
   * Setzt die H�he des Punktes in der Oktalbaumstruktur.
   * @param h H�he
   */
  void setHight(Hight h);

  /**
   * Setzt den Index in x-Richtung.
   * @param x x-Index
   */
  void setX(AxIndex x);

  /**
   * Setzt den Index in y-Richtung.
   * @param y y-Index
   */
  void setY(AxIndex y);

  /**
   * Setzt den Index in z-Richtung.
   * @param z z-Index
   */
  void setZ(AxIndex z);

  /**
   * Equivalent zu getCoordinate(axis).
   * @param axis Achsnummer
   * @return Index der Achse axis
   */
  AxIndex operator[](Axis axis);

 private:
  /**
   * Indizes des Punktes
   */
  AxIndex indices[DIMENSIONS];

  /**
   * H�he des Punktes
   */
  Hight hight;
};

/**
 * Referenzieren p1 und p2 den gleichen Knoten im Oktalbaum?
 * @param p1 erster Knotenvektor
 * @param p2 zweiter Knotenvektor
 * @return \f$ \forall i \in [0;\dim) : p_1[i]
 *                                      = p_2[i]
 *         \f$
 * @pre p1.getHight() = p2.getHight()
 */
bool operator==(NodeIndex p1, NodeIndex p2);

/**
 * Liegt p1 nach lexikographischer Ordnung vor p2?
 * @param p1 erster Knotenvektor
 * @param p2 zweiter Knotenvektor
 * @return \f$\exists i \in [0; \dim) :
 *            p_1[i] < p_2[i] ~ 
              \wedge ~ \forall k \in [0; i)  : p_1[k] = p_2[k] \f$
 * @pre p1.getHight() = p2.getHight()
 */
bool operator<(NodeIndex p1, NodeIndex p2);

#endif // ! __NODE_INDEX_H__

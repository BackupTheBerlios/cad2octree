/**
 * @file src/geom/polygon.h
 * Polygon aus geometrischen Punkten.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <surface.h>
#include <geom_point.h>
#include <line.h>

/**
 * Drei- oder Viereck. Die Eckpunkte sind geometrische Punkte (GeomPoint).
 */
class Polygon : public Surface {
 public:
  /**
   * Konstruktor. Erzeugt ein Dreieck.
   * @param pA erster Eckpunkt
   * @param pB zweiter Eckpunkt
   * @param pC dritter Eckpunkt
   */
  Polygon(GeomPoint pA, GeomPoint pB, GeomPoint pC);

  /**
   * Konstruktor. Erzeugt ein Viereck.
   * @param pA erster Eckpunkt
   * @param pB zweiter Eckpunkt
   * @param pC dritter Eckpunkt
   * @param pD vierter Eckpunkt
   * @pre alle vier Punkte müssen in einer Ebene liegen.
   */
  Polygon(GeomPoint pA, GeomPoint pB, GeomPoint pC, GeomPoint pD);

  /**
   * Liefert Die Anzahl der Eckpunkte.
   * @return \em 3, für Dreieck und \em 4, für Viereck
   */
  int getCount();

  /**
   * Liefert eine Kopie des Polygons.
   * @return Kopie
   */
  Polygon getDup();

  /**
   * Liefert die virtuelle Höhe des Polygons im Oktalbaum.
   * @return Polygonhöhe im Oktalbaum
   */
  virtual Hight getHight();

  /**
   * Liefert den auf der Ebene liegende Fußpunkt zu p.
   * Im entarteten Fall wird p zurückgegeben.
   * @param p Prüfpunkt
   * @return Fußpunkt zu p auf der Ebene
   */
  GeomPoint getFootpoint(GeomPoint p);

  /**
   * Liefert den normalisierten Normalenvektor zur Ebene.
   * Dieser Vektor steht senkrecht auf der Ebene und hat den Betrag 1, 
   * falls es sich um eine echte Ebene handelt.
   * Ist die Ebene entartet ist (Linie oder Punkt), wird ein Nullvektor
   * zurückgeliefert.
   * @return normalisierter Normalenvektor
   */
  GeomVec getNormVec();

  /**
   * Liefert den idx-ten Eckpunkt.
   * @param idx wievielter Eckpunkt
   * @return Eckpunkt Nr. idx
   * @pre 0 <= idx < getCount()
   */
  GeomPoint& getPoint(int idx);

  /**
   * Befindet sich p in diesem Polygon?
   * @param p Prüfpunkt
   * @return Ob sich p in diesem Polygon befindet.
   */
  virtual bool isIn(GeomPoint p);

  /**
   * Befindet p in der Ebene, die durch die ersten 3 Eckpunkte dieses Polygons
   * definiert ist?
   * @param p Prüfpunkt
   * @return Ob sich p in der Polygonebene befindet.
   */
  bool isInPlane(GeomPoint p);

  /**
   * Gibt dieses Polygon auf der Konsole aus.
   */
  void print();

  /**
   * Setzt die virtuelle Höhe des Polygons im Oktalbaum.
   * @param h Dreieckshöhe im Oktalbaum
   */
  void setHight(Hight h);

  virtual bool testLine(GeomPoint p, GeomPoint &q, 
			bool &intersect, bool &inside);

  /**
   * Liefert den idx-ten Eckpunkt.
   * @param idx wievielter Eckpunkt
   * @return Eckpunkt Nr. idx
   * @pre 0 <= idx < getCount()
   */
  GeomVec operator[](int idx);

 private:
  /**
   * Überprüft, ob sich q auf dem Polygonrand befindet.
   * @param p Prüfpunkt
   * @return Ob sich q auf dem Polygonrand befindet.
   */
  bool isAtBorder(GeomPoint p);

  /**
   * Ist p Eckpunkt dieses Polygons?
   * @return Ob p ein Eckpunkt ist
   */
  bool isCorner(GeomPoint p);

  /**
   * Liefert, ob q im Polygon liegt.
   * Es wird die Umlaufsinn-Methode auf die Projektionsebene, die durch proj 
   * gegeben ist, angewendet 
   * @param q zu betrachtender Punkt
   * @param proj Achse. Wird zur Festlegung der Projektionsebene benötigt.
   *             Die Achse proj entf"allt durch die Projektion. 
   * @pre isInPlane(q)
   */
  bool isIn(GeomPoint q, Axis proj);

  /**
   * Zahl der Eckpunkte. 3 bei Dreieck und 4 bei Viereck.
   */
  int cornerCount;

  /**
   * Eckpunkt A
   */
  GeomPoint pointA;

  /**
   * Eckpunkt B
   */
  GeomPoint pointB;

  /**
   * Eckpunkt C
   */
  GeomPoint pointC;

  /**
   * Eckpunkt D. Entspricht bei einem Dreieck pointC.
   */
  GeomPoint pointD;

}; // class Polygon

#endif // ! __POLYGON_H__

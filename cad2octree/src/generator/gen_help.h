/**
 * @file src/generator/gen_help.h
 * Bibliothek mit Hilfsfunktionen zum Generieren der Oktalbaumstruktur.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __GEN_HELP_H__
#define __GEN_HELP_H__

#include <point.h>
#include <quadrilateral.h>
#include <triangle.h>
#include <node_vec.h>
#include <polygon.h>
#include <exception.h>

/**
 * Klasse, die Routinen enthält, die zum Generieren der Oktalbaumstruktur
 * benötigt werden.
 *
 * Dies umfasst eine Konvertierungsfunktion: Point --> NodeIndex und
 * Methoden zum Berechnen der nächsten zunehmenden Achse zur Linienaproximation
 * basierend auf dem Cohem-Sutherland-Algorithmus
 * (in leicht abgewandelter Form).
 */
class GenHelp {
 public:
  /**
   * Konstruktor.
   * @param maxTreeHight maximale Höhe des Oktalbaums
   * @param minPoint unterer vorderer linker Punkt des umschließenden
   *          Quaders
   * @param maxPoint oberer hinterer rechter Punkt des umschließenden
   *          Quaders
   * @pre minPoint << maxPoint
   */
  GenHelp(Hight maxTreeHight, Point minPoint, Point maxPoint)
    throw (NotEnoughMemoryException);

  /**
   * Liefert die Achse, auf der weitergegangen werden muss, um die
   * Ideallinie am besten zu aproximieren.
   * Falls direction für alle Achsen 0 ist (Start- und Endpunkt der
   * Ideallinie sind gleich), wird die x-Achse zurückgeliefert.
   * Ansonsten werden nur Achsen berücksichtigt für die direction
   * ungleich 0 ist.
   * @param current aktueller Punkt
   * @param end End-Punkt
   * @param line Vektor der Ideallinie
   * @param direction Richtung der Ideallinie
   * @return die Achse, auf der am günstigen weitergegangen wird
   * @pre current.getHight() = end.getHight() = line.getHight()
   */
  Axis bestAxis(NodeIndex current, NodeIndex end, NodeVec line,
		Direction direction);

  /**
   * Liefert den zugehörigen Point des CadModel zum GeomPoint p.
   * @param p Punkt als GeomPoint
   * @return Point des CadModel
   * @pre p.getHight() == BASE_NODE_HIGHT
   */
  Point getCadPoint(GeomPoint p);

  /**
   * Liefert den zugehörigen GeomPoint zum Point p des CadModel.
   * @param p Punkt des CadModel
   * @return GeomPoint
   */
  GeomPoint getGeomPoint(Point p);

  /**
   * Liefert den zugehörigen Knotenindex zum Punkt p.
   * @param p Punkt des CadModel
   * @return Knoten-Index
   */
  NodeIndex getNodeIndex(Point p);

  /**
   * Liefert das zugehörige Polygon zum Quadrilateral q.
   * @param q Viereck des CadModel
   * @param t2 Falls die 4 Punkte nicht in einer Ebene, wird in t2 das obere
   *           und als Rückgabewert das untere Dreieck zurückgegeben. 
   *           Liegen die vier Punkte in einer Ebene wird t2 auf NULL gesetzt.
   * @return Polygon des Geometrie-Modells
   * @pre q != NULL
   */
  Polygon getPolygon(Quadrilateral *q, Polygon* &t2);  

  /**
   * Liefert das zugehörige Polygon zum Triangle t.
   * @param t Dreieck des CadModel
   * @return Polygon des Geometrie-Modells
   * @pre t != NULL
   */
  Polygon getPolygon(Triangle *t);  

 private:
  /**
   * Liefert die zugehörige Koordinate im CadModel zum Punkt p der Achse axis.
   * @param p Punkt als GeomPoint
   * @param axis Koordinaten-Achse
   * @return Koordinate im CadModel
   */
  Coordinate getCadCoord(GeomPoint p, Axis axis);

  /**
   * Liefert den Abstand des Testpunktes zur Ideallinie.
   * Je kleiner der Fehler, desto besser wird die Ideallinie
   * aproximiert.
   * @param fromTestpoint Strecke vom Testpunkt zum Endpunkt der Line
   * @param line Strecke vom Startpunkt zum Endpunkt der Ideallinie
   * @return vorzeichenloser Abstand zur Ideallinie
   * @pre fromTestpoint.getHight() = line.getHight()
   */
  Coordinate getError(NodeVec fromTestpoint, NodeVec line);

  /**
   * Liefert die zugehörige geometrische Koordinate zum Punkt p der Achse axis.
   * @param p Punkt des CadModel
   * @param axis Koordinaten-Achse
   * @return geometrische Koordinate (entspr. real-wertigen Index)
   */
  Coordinate getGeomCoord(Point p, Axis axis);

  /**
   * Liefert den größten Abstand entlang einer Koordinatenachse
   * zwischen den Punkten min und max
   * @param min 'kleiner' Punkt
   * @param max 'größerer' Punkt
   * @pre min << max
   */
  Coordinate getMaxExtent(Point min, Point max);
  
  /**
   * Reziproke der Kantenlänge eines Oktalwürfels auf der untersten Ebene
   */
  Coordinate density;

  /**
   * unterer hinterer linker Punkt des vom Oktalbaum beschriebenen
   * Areas
   */
  Point min;
};

#endif // ! __GEN_HELP_H__

/**
 * @file src/reader/dime_help.h
 * Hilfsklasse (dimeEntity --> CadModel).
 * Wird zum Erstellen des CadModel aus vom dime-Model
 * bereitgestellten Entities der DXF-Datei bereitgestellt.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DIME_HELP_H__
#define __DIME_HELP_H__

#include <cad/cad_model.h>

#include <dime/entities/3DFace.h>
#include <dime/entities/Entity.h>
#include <dime/entities/Polyline.h>
#include <dime/entities/Vertex.h>


/**
 * Klasse, die zum Erzeugen des CadModel aus dem dimeModel benötigt wird.
 */
class DimeHelp {
 public:
  /**
   * Konstruktor.
   * @param cadModel CadModel
   * @param color Farbe der zu erzeugenden Cad-Objekte
   * @param splitQuad \e true, wenn alle Vierecke der ENTITY 3DFACE als 
   *        zwei Dreiecke "ubertragen werden sollen. 
   * @pre cadModel != NULL
   * @pre color > 0
   */
  DimeHelp(CadModel* cadModel, Color color, bool splitQuad);

  /**
   * Fügt das aus entity erzeugte CadObject zum internen CadModel hinzu.
   * @param entity DXF-Entity des dimeModel
   * @pre entity != NULL 
   */
  void add(dimeEntity *entity);

  /**
   * Liefert das CadModel.
   * @return CadModel
   */
  CadModel* getCadModel();

 private:

  /**
   * Konvertiert den dimeVec3f v des dimeModel in ein Point.
   * @param v Punkt als dimeVec3f des dimeModel
   * @return v konvertiert als Point
   */
  static Point vertex2Point(dimeVec3f v);

  /**
   * Fügt die aus entity generierte ebene Fläche zum internen CadModel
   * hinzu.
   * @param entity DXF-3dFace des dimeModel
   */
  void addPlane(dime3DFace* entity);

  /**
   * Fügt die aus entity generierte Spline-Fläche zum internen CadModel
   * hinzu.
   * @param entity DXF-Polyline des dimeModel
   */
  void addSpline(dimePolyline* entity);

  /**
   * internes CadModel
   */
  CadModel* cadModel;

  /**
   * Farbe der neuen Cad-Objekte.
   */
  Color color;

  /**
   * Anzahl der Kontrollpunkte im Modell.
   */
  unsigned countCP;

  /**
   * Anzahl der Vierecke im Modell.
   */
  unsigned countQuad;

  /**
   * Anzahl der Spline-Flächen im Modell.
   */
  unsigned countSplineFaces;

  /**
   * Anzahl der Dreiecke im Modell.
   */
  unsigned countTriangles;

  /**
   * Anzahl der Vertex im Modell.
   */
  unsigned countVertices;

  /**
   * Sollen alle Vierecke als 2 Dreicke ins cadModel übertragen werden?
   */
  bool splitQuadrilaterals;

}; // class DimeHelp

#endif // ! __DIME_HELP_H__

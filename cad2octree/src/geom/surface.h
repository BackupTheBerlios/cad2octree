/**
 * @file src/geom/surface.h
 * Oberfläche, die durch geometrische Punkte definiert ist.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <geom_point.h>

/**
 * Oberfläche, die durch geometrische Punkte definiert ist.
 */
class Surface {
 public:
  /**
   * Liefert die virtuelle Höhe der Oberfläche im Oktalbaum.
   * @return Oberflächenhöhe im Oktalbaum
   */
  virtual Hight getHight()= 0;  

  /**
   * Befindet sich p auf dieser Oberfläche?
   * @param p Prüfpunkt
   * @return Ob sich p auf dieser Oberfläche befindet.
   */
  virtual bool isIn(GeomPoint p)= 0;

  /**
   * Setzt die virtuelle Höhe der Oberfläche im Oktalbaum.
   * @param h Höhe
   */
  virtual void setHight(Hight h)= 0;  

  /**
   * Liefert die Lage, falls testLine() erfolgreich war.
   * @param p Ausgangspunkt
   * @param q den Schnittpunkt, falls die Testlinie die Oberfläche schneidet
   * @param intersect die Testlinie, die parallel zur Achse RAY_AXIS durch p 
   *                  verläuft, schneitet das Polygon.
   * @param inside true, falls der Orientierungsvektor der Oberfläche bei q 
   *                     in Richtung p verläuft.
   * @return true, falls die Testlinie nicht in der Polygonebene liegt
   */
  virtual bool testLine(GeomPoint p, GeomPoint &q, bool &intersect, 
			bool &inside)= 0;

}; // class Surface

#endif // ! __SURFACE_H__

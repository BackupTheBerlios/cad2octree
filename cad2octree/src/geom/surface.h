/**
 * @file src/geom/surface.h
 * Oberfl�che, die durch geometrische Punkte definiert ist.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <geom_point.h>

/**
 * Oberfl�che, die durch geometrische Punkte definiert ist.
 */
class Surface {
 public:
  /**
   * Liefert die virtuelle H�he der Oberfl�che im Oktalbaum.
   * @return Oberfl�chenh�he im Oktalbaum
   */
  virtual Hight getHight()= 0;  

  /**
   * Befindet sich p auf dieser Oberfl�che?
   * @param p Pr�fpunkt
   * @return Ob sich p auf dieser Oberfl�che befindet.
   */
  virtual bool isIn(GeomPoint p)= 0;

  /**
   * Setzt die virtuelle H�he der Oberfl�che im Oktalbaum.
   * @param h H�he
   */
  virtual void setHight(Hight h)= 0;  

  /**
   * Liefert die Lage, falls testLine() erfolgreich war.
   * @param p Ausgangspunkt
   * @param q den Schnittpunkt, falls die Testlinie die Oberfl�che schneidet
   * @param intersect die Testlinie, die parallel zur Achse RAY_AXIS durch p 
   *                  verl�uft, schneitet das Polygon.
   * @param inside true, falls der Orientierungsvektor der Oberfl�che bei q 
   *                     in Richtung p verl�uft.
   * @return true, falls die Testlinie nicht in der Polygonebene liegt
   */
  virtual bool testLine(GeomPoint p, GeomPoint &q, bool &intersect, 
			bool &inside)= 0;

}; // class Surface

#endif // ! __SURFACE_H__

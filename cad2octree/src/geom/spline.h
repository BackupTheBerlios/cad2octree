/**
 * @file src/geom/spline.h
 * Spline-Fl�che, die �ber ihre geometrischen Punkte definiert ist.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __SPLINE_H__
#define __SPLINE_H__

#include <surface.h>
#include <b_spline.h>
#include <generator/oct_gen.h>

/**
 * Spline-Fl�che, die �ber ihre geometrischen Punkte definiert ist.
 */
class Spline : public Surface {
 public:
  /**
   * Konstruktor.
   * @param bSpline zugrundeliegende B-Spline des CadModel.
   * @param generator Oktalbaum-Generator.
   */
  Spline(BSpline bSpline, OctGen* generator);

  /**
   * Destruktor.
   */
  virtual ~Spline();

  /**
   * F�gt die Spline-Fl�che zum Oktalbaum hinzu.
   * @param color zu verwendete Farbe
   */
  void addToOctree(Color color);

  virtual Hight getHight();

  virtual bool isIn(GeomPoint p);

  virtual void setHight(Hight h);

  virtual bool testLine(GeomPoint p, GeomPoint &q, 
			bool &intersect, bool &inside);

  /**
   * Gibt die Kontrollpunkte auf der Konsole aus.
   */
  virtual void print();

 private:
  /**
   * Ausdehnungsrichtung
   */
  typedef BSpline::EXTENT EXTENT;

  /**
   * Liefert die Basis-Funktionen in N.
   * @param axis M_DIR oder N_DIR
   * @param i Knotenspannindex
   * @param u Indexparameter
   * @param N die ermittelten Basisfunktionen
   */
  void basisFuns(EXTENT axis, int i, Coordinate u, Coordinate N[]);

  /**
   * Lokalisiert einen Punkt anhand dem Oberfl�chenpolygonnetz der Spline.
   * @param p Ausgangspunkt
   * @param q den Schnittpunkt, falls die Testlinie die Oberfl�che schneidet
   * @param intersect die Testlinie, die parallel zur Achse RAY_AXIS durch p
   *                  verl�uft, schneitet das Polygon.
   * @param inside true, falls der Orientierungsvektor der Oberfl�che bei q
   *                     in Richtung p verl�uft.
   * @return true, falls die Testlinie nicht in der Polygonebene liegt
   */
  bool chkSplinePart(GeomPoint p, 
		     GeomPoint &q, bool &intersect, bool &inside);

  /**
   * Liefert den Knotenspannindex.
   * @param axis M_DIR oder N_DIR
   * @param u Indexparameter
   * @return Knotenspannindex
   */
  int findSpan(EXTENT axis, Coordinate u); 

  /**
   * Liefert den Kontrollpunkt (m_idx; n_idx).
   * @return m_idx-ten Laufzahl in  M-Richtung
   * @return n_idx-ten Laufzahl in N-Richtung
   */
  GeomPoint getCP(int m_idx, int n_idx);

  /**
   * Liefert den zugeh�rigen Knotenindex der Spline-Fl�che zu
   * den Parameter (u; v).
   * @param u Parameter in M-Richtung
   * @param v Parameter in N-Richtung
   * @return zugeh�riger Knotenindex auf der Spline-Oberfl�che
   * @pre gen!= NULL
   */
  NodeIndex getFaceIndex(Coordinate u, Coordinate v);

  /**
   * Liefert den zugeh�rigen Punkt der Spline-Fl�che zu 
   * den Parameter (u; v).
   * @param u Parameter in M-Richtung
   * @param v Parameter in N-Richtung
   * @return zugeh�rigen Fl�chenpunkt
   * @pre gen!= NULL
   */
  GeomPoint getFacePoint(Coordinate u, Coordinate v);

  /**
   * Liefert die Zahl der zu errechneten Zwischenpunkte auf der Fl�che.
   * @param axis M_DIR oder N_DIR
   * @return Verfeinerungszahl
   */
  AxIndex getGranulty(EXTENT axis);

  /**
   * Verwendeter Oktalbaumgenerator.
   */
  OctGen* gen;
  
  /**
   * H�he der Fl�che im Oktalbaum.
   */
  Hight h;

  /**
   * Zugrundeliegende B-Spline des CAD-Modells.
   */
  BSpline spl;

};

#endif // ! __SPLINE_H__

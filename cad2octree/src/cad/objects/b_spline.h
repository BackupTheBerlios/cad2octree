/**
 * @file src/cad/objects/b_spline.h
 * Spline-Fläche.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __B_SPLINE_H__
#define __B_SPLINE_H__

#include <face.h>
#include <point.h>

#include <vector>

/**
 * Grad der Spline.
 */
#define DEGREE 3

/**
 * B-Spline-Fläche.
 */
class BSpline : public Face {
 public:
  /**
   * Ausdehnungsrichtung
   */
  enum EXTENT { M_DIR= 0, ///< M-Richtung
		N_DIR= 1  ///< N-Richtung
  };

  /**
   * Konstruktor.
   * @param m_count #Kontrollpunkte in M-Richtung
   * @param pMeshClosedM Ob die Spline-Fläche in M-Richtung geschlossen ist.
   * @param n_count #Kontrollpunkte in N-Richtung
   * @param pMeshClosedN Ob die Spline-Fläche in N-Richtung geschlossen ist.
   */
  BSpline(int m_count, bool pMeshClosedM, int n_count, bool pMeshClosedN);

  /**
   * Destruktor.
   */
  virtual ~BSpline();

  /**
   * Fügt den Kontrollpunkt p zur Spline-Fläche hinzu.
   * @param p Kontrollpunkt
   */
  void addCP(Point p);

  /**
   * Liefert den Kontrollpunkt (m_idx; n_idx).
   * @return m_idx-ten Laufzahl in M-Richtung
   * @return n_idx-ten Laufzahl in N-Richtung
   */
  Point getControlPoint(int m_idx, int n_idx);

  /**
   * Liefert die Anzahl der Kontrollpunkte in M- oder N-Richtung.
   * @param axis M_DIR oder N_DIR
   * @return #Kontrollpunkte in diese Richtung
   * @pre axis = M_DIR or axis = N_DIR
   */
  int getCount(EXTENT axis);

  /**
   * Liefert die Art des CAD-Objekts zurück.
   * @return CadObject::SPLINE
   */
  virtual const DataType getDataType();

  /**
   * Liefert den n_idx-ten Knoten in axis-Richtung.
   * @param axis M_DIR oder N_DIR
   * @param n_idx Laufzahl
   * @return n_idx-ter Knoten
   */
  int getKnot(EXTENT axis, int n_idx);

  /**
   * Liefert die Größe des Knotenvektors in axis-Richtung.
   * @param axis M_DIR oder N_DIR
   * @return Dimension des Knotenvektors
   */
  int getKnotCount(EXTENT axis);

  /**
   * Liefert die Maximalgröße eines Knotens in axis-Richtung.
   * @param axis M_DIR oder N_DIR
   * @return Maximale Knotengröße
   */
  int getKnotMax(EXTENT axis);

  /**
   * Liefert die Minimalgröße eines Knotens in axis-Richtung.
   * @param axis M_DIR oder N_DIR
   * @return Minimale Knotengröße
   */
  int getKnotMin(EXTENT axis);

  /**
   * Liefert den Punkt zurück, der jeweils das Maximum aller
   * Eckpunktkoordinaten enthält.
   * @return vorderer oberer rechter Punkt des ebenen Flächenobjekts
   *         umschließenden Quaders
   * @pre getCount(M_DIR) > 0
   */
  virtual Point getMaxPoint();

  /**
   * Liefert den Punkt zurück, der jeweils das Minimum aller
   * Eckpunktkoordinaten enthält.
   * @return hinterer unterer linker Punkt des ebenen Flächenobjekts
   *         umschließenden Quaders
   * @pre getCount(M_DIR) > 0
   */
  virtual Point getMinPoint();

  /**
   * Ist die Spine-Fläche in axis-Richtung geschlossen?
   * @param axis M_DIR oder N_DIR
   * @return Ob die Spline-Fläche in Richtung axis geschlossen ist.
   */
  bool isClosed(EXTENT axis);

  /**
   * Gibt die Kontrollpunkte auf der Konsole aus.
   */
  virtual void print();

 private:
  /**
   * Typ für alle Kontrollpunkte der Splinefläche.
   * Kontrollpunkte in M- und in N-Richtung.
   */
  typedef vector<Point> CPContainer;

  /**
   * Spline-Fläche in M-Richtung geschlossen?
   */
  bool closedM;

  /**
   * Spline-Fläche in N-Richtung geschlossen?
   */
  bool closedN;

  /**
   * Kontrollpunkte der Spline-Fläche.
   */
  CPContainer controlPoints;

  /**
   * Anzahl d. Kontrollpunkte in M-Richtung
   */
  int countM;

  /**
   * Anzahl d. Kontrollpunkte in N-Richtung
   */
  int countN;

};

#endif // ! __BSPLINE_H__

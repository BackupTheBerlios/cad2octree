/**
 * @file src/geom/line.h
 * Line, die durch 2 Knotenindizes geht.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __LINE_H__
#define __LINE_H__

#include <geom_vec.h>

/**
 * Eine Line, die durch 2 Punkte geht.
 */
class Line {
 public:
  /**
   * Konstruktor.
   * @param pA erster Punkt
   * @param pB zweiter Punkt
   * @pre pA.getHight() = pB.getHight()
   */
  Line(GeomPoint pA, GeomPoint pB);

  /**
   * Liefert die Anzahl der Endpunkte
   * @return 2
   */
  int getCount();

  /**
   * Liefert den Richtungsvektor.
   * @return pB - pA
   */
  GeomVec getDirVec();

  /**
   * Liefert den Abstandsvektor von p zum Fu�punkt. 
   * @param p Pr�fpunkt
   * @return Abstandsvektor
   * @pre p.getHight() = getHight()
   */
  GeomVec getDistVec(GeomPoint p);

  /**
   * Liefert den Fu�punkt von p auf der Linie.
   * Der Fu�punkt ist der Punkt auf der Geraden, der den geringsten Abstand
   * zu p hat.
   * @param p Pr�fpunkt
   * @return Fu�punkt von p
   */
  GeomPoint getFootpoint(GeomPoint p);

  /**
   * Liefert die virtuelle H�he der Linie.
   * @return Linienh�he
   */
  Hight getHight();

  /**
   * Liefert den idx-ten Endpunkt.
   * @param idx wievielter Endpunkt
   * @return Endpunkt Nr. idx
   * @pre 0 <= idx < 2
   */
  GeomPoint getPoint(int idx);

  /**
   * Befindet sich p auf der Geraden, die durch diese Linie gegeben ist?
   * @param p Pr�fpunkt
   * @return Ob sich p auf der Geraden befindet.
   * @pre p.getHight() = getHight()
   */
  bool isAtLine(GeomPoint p);

  /**
   * Ist p Endpunkt dieser Linie?
   * @return Ob p ein Endpunkt ist
   * @pre p.getHight() = getHight()
   */
  bool isEndpoint(GeomPoint p);

  /**
   * Befindet sich p auf dieser Line zwischen den beiden Punkten?
   * @param p Pr�fpunkt
   * @return Ob sich p auf dieser Linie befindet.
   * @pre p.getHight() = getHight()
   */
  bool isInStretch(GeomPoint p);

  /**
   * Gibt diese Linie auf der Konsole aus.
   */
  void print();

  /**
   * Setzt die virtuelle H�he der Linie.
   * @param h Linienh�he
   */
  void setHight(Hight h);

  /**
   * Liefert den idx-ten Punkt.
   * @param idx wievielter Punkt
   * @return Eckpunkt Nr. idx
   * @pre 0 <= idx < 2
   */
  GeomPoint operator[](int idx);

 private:
  /**
   * Punkt A
   */
  GeomPoint pointA;

  /**
   * Punkt B
   */
  GeomPoint pointB;
}; // class Line

#endif // ! __LINE_H__

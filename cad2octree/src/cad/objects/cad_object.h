/**
 * @file src/cad/objects/cad_object.h
 * Definiert allgemeine Methoden zur Beschreibung eines CAD-Objekts.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __CAD_OBJECT_H__
#define __CAD_OBJECT_H__

class Point;

/**
 * Abstrakte Klasse für alle CAD-Objekte.
 *
 * Dies kann eine Fläche (Face) oder ein Punkt (Point)
 * sein.
 */
class CadObject {
 public:
  /**
   * Um was für ein CAD-Objekt handelt es sich?
   */
  enum DataType {TRIANGLE,        ///< Dreieck
		 QUADRILATERAL,   ///< Viereck
		 B_SPLINE,        ///< B-Spline-Fläche
		 POINT            ///< Punkt
  };
 
  /**
   * Liefert die Art des CAD_Objekts zurück.
   * @return um welches CAD-Objekt es sich handelt
   */
  virtual const DataType getDataType()= 0;

  /**
   * Liefert zurück, wieviele Dimensionen das CAD-Objekt besitzt.
   * @return Dimensionalität das CAD-Objekts
   */
  virtual int getDimension()= 0;

  /**
   * Liefert den Punkt zurück, der jeweils das Maximum aller
   * das CAD-Objekt beschreibenden Koordinaten enthält.
   * @return hinterer oberer rechter Punkt des CAD-Objekt umschließenden
   *         Quaders
   */
  virtual Point getMaxPoint()= 0;

  /**
   * Liefert den Punkt zurück, der jeweils das Minimum aller
   * das CAD-Objekt beschreibenden Koordinaten enthält.
   * @return vorderer unterer linker Punkt des CAD-Objekt umschließenden
   *         Quaders
   */
  virtual Point getMinPoint()= 0;

  /**
   * Ist das Objekt eben?
   * @return false
   */
  virtual bool isPlane();

  /**
   * Liefert einen Point der das jeweilige Maximum der Koordinaten 
   * zwischen dem internen maxPoint und dem Point p enthält.
   * @param p Vergleichspunkt
   * @return \f$ \sum_{i=0}^{\dim-1} \max \{ \mbox{getMinPoint()[i]}, p[i] \}
   *                                 \ast \vec e_i \f$ 
   */
  Point max(Point p);

  /**
   * Liefert einen Point der das jeweilige Minimum der Koordinaten 
   * zwischen dem internen maxPoint und dem Point p enthält.
   * @param p Vergleichspunkt
   * @return \f$ \sum_{i=0}^{\dim-1} \min \{ \mbox{getMinPoint()[i]}, p[i] \}
   *                                 \ast \vec e_i \f$ 
   */
  Point min(Point p);

  /**
   * Gibt die das CAD-Objekt beschreibenden Geometriedaten auf
   * der Konsole aus.
   */
  virtual void print()= 0;

};

#endif // ! __CAD_OBJECT_H__

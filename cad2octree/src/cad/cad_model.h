/**
 * @file src/cad/cad_model.h
 * Enthält Container für alle CAD-Objekte.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */
#ifndef __CAD_MODEL_H__
#define __CAD_MODEL_H__

#include <cad/container/faces.h>
#include <point.h>

/**
 * Container, der alle CAD-Objekte enthält.
 *
 * Der Iterator wird intern gehalten und kann über first() und next() 
 * gesteuert werden.
 * 
 * Beispiel: \include cad_model_iteration.cpp.func
 *
 */
class CadModel : public Faces {
 public:
  /**
   * Default-Konstruktor.
   */
  CadModel();

  /**
   * Fügt object zum CadModel hinzu, falls es noch nicht im CadModel existiert.
   * minPoint (\ref getMinPoint()) und maxPoint (\ref getMaxPoint()) werden
   * angepasst.
   * 
   * @param object hinzuzufügender Punkt
   * @param color Farbe von object
   * @pre object != NULL
   */
  void add(Element object, Color color);

  /**
   * Liefert den 'äußersten Punkt oben rechts hinten' des Areals zurück, indem
   * alle Objekte des CadModel-Container liegen.
   * @return \f$ \sum_{i=0}^{\dim-1} \max_{p \in \mbox{CadModel-Container}}
   *                                   \{ p[i] \} * \vec e_i \f$ 
   */
  Point getMaxPoint();

  /**
   * Liefert den 'äußersten Punkt unten links vorne' des Areals zurück, indem
   * alle Objekte des CadModel-Container liegen.
   * @return \f$ \sum_{i=0}^{\dim-1} \min_{p \in \mbox{CadModel-Container}}
   *                                   \{ p[i] \} * \vec e_i \f$ 
   */
  Point getMinPoint();

  /**
   * Liefert die Farbe des Objekts zurück, auf dem gerade der interne
   * Cursor des Containers steht.
   * @exception OutOfModelException falls hasObject()==false
   * @return Farbe des aktuellen Elements
   */
  Color getObjColor() throw (OutOfModelException*);

  /**
   * Gibt alle im CadModel-Container enthaltene Elemente auf der Konsole
   * aus.
   *
   * Falls der CadModel-Container leer ist, wird \n
   * <tt>CadModel: leer.</tt>\n
   * ausgegeben.
   */
  void print();  

 private:
  /**
   * 'äußerster Punkt oben rechts vorne'
   * @see getMaxPoint()
   * @see Point::max()
   */
  Point maxPoint;

  /**
   * 'äußerster Punkt unten links hinten'
   * @see getMinPoint()
   * @see Point::min()
   */
  Point minPoint;

  /**
   * Farbe der Container-Objekte.
   */
  Color objColor;

}; // class CadModel

#endif // ! __CAD_MODEL_H__

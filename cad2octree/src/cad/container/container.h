/**
 * @file src/cad/container/container.h
 * Interface für Container für CAD-Objekte.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <exception.h>
#include <cad/objects/face.h>

/**
 * Typ für die Container-Objekte.
 */
typedef Face* Element;

/**
 * Interface für Container für CAD-Objekte.
 */
class Container {
 public:
  // ##### Exceptions ################################################
  /**
   * Wird geworfen, wenn versucht wird ein nichtvorhandenes
   * CadObject aus dem CadModel zu lesen oder zu manipulieren.
   */
  class OutOfModelException : Exception {
  public:
    /**
     * Exception-Konstruktor.
     */
    OutOfModelException() : Exception("Access out of CadModel-Container") {}
  };

  // ##### Container #################################################
  /**
   * Fügt object zum Container hinzu.
   * @object hinzuzufügendes Element
   * @pre object != NULL
   */
  virtual void add(Element object)= 0;

  /**
   * Liefert zurück, wieviele Objekte sich im Container befinden.
   * @return Anzahl der Objekte im Container
   */
  virtual unsigned count()= 0;

  /**
   * Ist kein Objekt im Container vorhanden?
   * @return true,  falls sich kein Objekt im Container befindet\n
   *         false, sonst
   */
  virtual bool empty()= 0;

  /**
   * Ist object im Container vorhanden?
   *
   * @param object zu suchendes Objekt
   * @return true,  falls object im Container existiert\n
   *         false, sonst
   */
  virtual bool exist(Element object)= 0;

  /**
   * Setzt den internen Cursor des Containers auf das erste Element.
   *
   * Falls der Container leer ist, wirft ein anschließender
   * Aufruf von getObject() oder next() eine OutOfModelException.
   */
  virtual void first()= 0;

  /**
   * Liefert das Objekt zurück, auf dem gerade der interne Cursor des
   * Containers steht.
   * @exception OutOfModelException falls hasObject()==false
   * @return aktuelles Element
   */
  virtual CadObject* getObject() throw (OutOfModelException*)= 0;

  /**
   * Befindet sich der interne Cursor innerhalb des Container? 
   * @return \em false, falls der Cursor sich außerhalb des Containers
   *                    (z.B. hinter dem letzten Element) befindet\n
   *         \em true,  sonst
   */
  virtual bool hasObject()= 0;

  /**
   * Setzt den internen Cursor auf das nachfolgende Element.
   * @exception OutOfModelException hasObject() lieferte bereits
   *              vor der Anwendung von next() false zurück.
   */
  virtual void next() throw (OutOfModelException*)= 0;

  /**
   * Gibt alle im Container enthaltene Elemente auf der Konsole aus.
   */
  virtual void print()= 0;

}; // class Container

#endif // ! __CONTAINER_H__

/**
 * @file src/cad/container/faces.h
 * Container f�r Oberfl�chen.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */
#ifndef __FACES_H__
#define __FACES_H__

#include <cad/container/container.h>
#include <cad/objects/face.h>

#include <slist>

/**
 * Container f�r Oberfl�chen.
 */
class Faces : public Container {
 public:
  struct Iterator;

  /**
   * Default-Konstruktor.
   */
  Faces();

  /**
   * Konstuktor. Es wird object im Face-Container abgelegt.
   * @param object Oberfl�chen-Objekt
   */
  Faces(Face* object);

  /**
   * Destruktor.
   */
  virtual ~Faces();

  /**
   * F�gt object zum Container hinzu.
   * @object hinzuzuf�gendes Element
   * @pre object != NULL
   */
  void add(Face* object);

  /**
   * Liefert zur�ck, wieviele Objekte sich im Container befinden.
   * @return Anzahl der Objekte im Container
   */
  void clear();

  /**
   * Liefert zur�ck, wieviele Objekte sich im Container befinden.
   * @return Anzahl der Objekte im Container
   */
  unsigned count();

  /**
   * Ist kein Objekt im Container vorhanden?
   * @return true,  falls sich kein Objekt im Container befindet\n
   *         false, sonst
   */
  bool empty();

  /**
   * Setzt den internen Cursor des Containers auf das erste Element.
   *
   * Falls der Container leer ist, wirft ein anschlie�ender
   * Aufruf von getObject() oder next() eine OutOfModelException.
   */
  void first();

  /**
   * Liefert das Objekt zur�ck, auf dem gerade der interne Cursor des
   * Containers steht.
   * @exception OutOfModelException falls hasObject()==false
   * @return aktuelles Element
   */
  Element getObject() throw (OutOfModelException*);

  /**
   * Befindet sich der interne Cursor innerhalb des Container? 
   * @return \em false, falls der Cursor sich au�erhalb des Containers
   *                    (z.B. hinter dem letzten Element) befindet\n
   *         \em true,  sonst
   */
  bool hasObject();

  /**
   * Setzt den internen Cursor auf das nachfolgende Element.
   * @exception OutOfModelException hasObject() lieferte bereits
   *              vor der Anwendung von next() false zur�ck.
   */
  void next() throw (OutOfModelException*);

  /**
   * Gibt alle im Container enthaltene Elemente auf der Konsole aus.
   */
  void print();

 private:
  /**
   * Typ f�r Oberfl�chen-Container.
   */
  typedef slist<Face *> FaceContainer;

  /**
   * Ist object im Container vorhanden?
   *
   * @param object zu suchendes Objekt
   * @return true,  falls object im Container existiert\n
   *         false, sonst
   */
  bool exist(Face* object);

  /**
   * Ist das Iterator-Objekt im Container vorhanden.
   * @param it Cursor
   * @return Ob der Cursor auf ein Objekt des Containers zeigt.
   */
  bool exist(Iterator it);

  /**
   * Sucht object im Container.
   * @param object zu suchendes Objekt
   * @return Cursor auf das erste Element im Container, welches mit
   *         object identisch ist. Falls object nicht im Container
   *         vorhanden ist, wird ein Cursor, der sich au�erhalb des
   *         Containers befindet zur�ckgegeben.
   */
  Iterator find(Face* object);

  /**
   * Interner Iterator. Zum Traversieren �ber alle Container-Objekte
   * ben�tigt.
   */
  struct Iterator {
    /**
     * Iterator des FaceContainer.
     */
    FaceContainer::iterator faceIt;
  };

  /**
   * Cursor auf das aktuelle Objekt des Containers.
   */
  Iterator current_object;

  /**
   * Oberfl�chen-Container.
   */
  FaceContainer objs;
}; // class Faces

#endif // ! __Faces_H__

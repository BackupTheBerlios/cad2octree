/**
 * @file src/cad/container/points.h
 * Container für Punkte. Zu jedem Punkt werden dabei die zugehörigen
 * Oberflächen gespeichert.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */
#ifndef __POINTS_H__
#define __POINTS_H__

#include <cad/container/container.h>
#include <cad/container/faces.h>
#include <cad/objects/point.h>

#include <map>

/**
 * Container für Punkte mit den dazugehörigen Oberflächen.
 */
class Points : public Container {
 public:
  struct Iterator;

  Points();

  virtual ~Points();

  void add(Face* object);

  void clear();

  unsigned count();

  bool empty();

  void first();

  Element getObject() throw (OutOfModelException*);

  //  Iterator getPosition();

  bool hasObject();

  void next() throw (OutOfModelException*);

  void print();

  //void setPosition(Iterator position);

  //  void operator+=(Points addPoints);

 private:
  typedef map<Point, Faces> ObjectContainer;

  struct Iterator { ObjectContainer::iterator pointIt; };

  bool exist(Element object);

  bool exist(Iterator it);

  bool exist(Point p);

  Iterator find(Element object);

  Iterator find(Point p);

  Iterator current_obj;

  ObjectContainer objs;
}; // class Points

#endif // ! __POINTS_H__

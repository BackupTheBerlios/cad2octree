/**
 * @file src/cad/container/solids.h
 * Container für Körper. Zu jedem Körper werden dabei die zugehörigen
 * 'Randpunkte' gespeichert.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */
#ifndef __SOLIDS_H__
#define __SOLIDS_H__

#include <cad/container/container.h>
#include <cad/container/points.h>

#include <slist>

/**
 * Container für Körper mit den dazugehörigen 'Randpunkten'.
 */
class Solids : public Container {
 public:
  struct Iterator;

  Solids();

  virtual ~Solids();

  void add(Element object);

  void add(Element object, Color color);

  virtual unsigned count();

  virtual bool empty();

  virtual bool exist(Element object);

  bool exist(Iterator it);

  Iterator find(Element object, Color color);

  Iterator find(Point point, Color color);

  virtual void first();

  virtual Element getObject() throw (OutOfModelException*);

  Color getObjColor() throw (OutOfModelException*);

  virtual Iterator getPosition();

  virtual bool hasObject();

  virtual void next() throw (OutOfModelException*);

  virtual void print();

  void setPosition(Iterator position);

  void operator+=(Solids addSolids);

 private:
  struct Solid {
    Color color;
    Points points;
  };

  typedef slist<Solid> ObjectContainer;

  struct Iterator {
    ObjectContainer::iterator solidIt;
    Points::Iterator rest;
  };

  Iterator current_obj;

  ObjectContainer objs;
}; // class Solids

#endif // ! __SOLIDS_H__

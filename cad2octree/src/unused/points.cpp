/**
 * file: src/cad/container/points.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/container/points.h>

#include <iostream>

// ##### Points() ####################################################
Points::Points() {
  //  first();
}


// ##### ~Points() ###################################################
Points::~Points() {
}

// ##### add() #######################################################
void Points::add(Element object) {
  assert (object != NULL);

  for (int i= 0; i < object->getBorderPointCount(); ++i) {
    Iterator it= find((*object)[i]);
    if (exist(it)) {
      it.pointIt->second.add(object);
    } else {
      /*      Faces newFaces;
      newFaces.add(object);
      */
      objs.insert(ObjectContainer::value_type((*object)[i], object));
    }
  }
}

// ##### clear() #####################################################
void Points::clear() {
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    it->second.clear();
  }
  objs.clear();
}

// ##### count() #####################################################
unsigned Points::count() {
  unsigned sum= 0;
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    sum+= it->second.count();
    //    ++sum;
  }
  return sum;
}

// ##### empty() #####################################################
bool Points::empty() {
  return objs.empty();
}

// ##### exist() #####################################################
bool Points::exist(Element object) {
  Iterator it= find(object);
  return exist(it);
}

// ##### exist() 
bool Points::exist(Iterator it) {
  return it.pointIt != objs.end();
}

// ##### find() ######################################################
Points::Iterator Points::find(Element object) {
  Iterator it= find((*object)[0]);
  return Iterator(it);
}

// ##### find() 
Points::Iterator Points::find(Point p) {
  Iterator it;
  it.pointIt= objs.find(p);
  return Iterator(it);
}

// ##### first() #####################################################
void Points::first() {
  current_obj.pointIt= objs.begin();
  if (exist(current_obj)) {
    current_obj.pointIt->second.first();
  }
}

// ##### getObject() #################################################
Element Points::getObject() throw (OutOfModelException*) {
  if (!hasObject()) { 
    throw new OutOfModelException();
  }
  return current_obj.pointIt->second.getObject();
}

// ##### getPosition() ###############################################
/*
Points::Iterator Points::getPosition() {
  return Iterator(current_obj);
  }*/

// ##### hasObject() #################################################
bool Points::hasObject() {
  return exist(current_obj);
}

// ##### next() ######################################################
void Points::next() throw (OutOfModelException*) {
  if (!hasObject()) {
    throw new OutOfModelException();
  }
  current_obj.pointIt->second.next();
  if (!current_obj.pointIt->second.hasObject()) {
    ++current_obj.pointIt;
    current_obj.pointIt->second.first();
  }
}

// ##### print() #####################################################
void Points::print() {
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    cout << "\t* ";
    Point(it->first).print();
    cout << endl;
    it->second.print();
  }
}

// ##### setPosition() ###############################################
/*
void Points::setPosition(Iterator position) {
  current_obj= position;
  }*/

// ##### operator+= ##################################################
/*void Points::operator+=(Points addPoints) {
  addPoints.first();
  while (addPoints.hasObject()) {
    add(addPoints.getObject());
    addPoints.next();
  }
  }*/

// EOF: src/cad/container/points.cpp

/**
 * file: src/cad/container/solids.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/container/solids.h>

#include <iostream>

// ##### Solids() ####################################################
Solids::Solids() {
  cerr << "Solids::Solids()" << endl;
  first();
  cerr << "solids() end" << endl;
}


// ##### ~Solids() ###################################################
Solids::~Solids() {
  objs.clear();
}

// ##### add() #######################################################
void Solids::add(Element object, Color color) {
  assert (object != NULL);

  Points points;
  cerr << "Solids::add()" << endl;
  for (int i= 0; i < object->getBorderPointCount(); ++i) {
    cerr << "find ";
    ((*object)[i]).print();
    cerr << endl;
    Iterator it= find((*object)[i], color);
    while (exist(it)) {
      cerr << "in exist";
      points+= it.solidIt->points;
      objs.erase(it.solidIt);
    }
  }
  cerr << "add-points" << endl;
  points.add(object);
  Solid newSolid;
  newSolid.points= points;
  newSolid.color= color;
  objs.insert(objs.begin(), newSolid);
  cerr << "solid-add end" << endl;
}

// ##### count() #####################################################
unsigned Solids::count() {
  unsigned sum= 0;
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    sum+= it->points.count();
  }
  return sum;
}

// ##### empty() #####################################################
bool Solids::empty() {
  return objs.empty();
}

// ##### exist() #####################################################
bool Solids::exist(Element object) {
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    Points::Iterator pointIt= it->points.find(object);
    if (it->points.exist(pointIt)) {
      return true;
    }
  }
  return false;
}

// ##### exist() #####################################################
bool Solids::exist(Iterator it) {
  return it.solidIt != objs.end();
}

// ##### find() ######################################################
Solids::Iterator Solids::find(Element object, Color color) {
  Iterator retVal;
  cerr << "solids::find()" << endl;
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    cerr << "in for" << endl;
    if (it->color == color) {
      cerr << "in if: points-find" << endl;
      Points::Iterator pointIt= it->points.find(object);
      cerr << "points exist";
      if (it->points.exist(pointIt)) {
	retVal.solidIt= it;
	retVal.rest= pointIt;
	return Iterator(retVal);
      }
    }
  }
  retVal.solidIt= objs.end();
  return Iterator(retVal);
}

// ##### find() 
Solids::Iterator Solids::find(Point p, Color color) {
  Iterator retVal;
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    if (it->color == color) {
      Points::Iterator pointIt= it->points.find(p);
      if (it->points.exist(pointIt)) {
	retVal.solidIt= it;
	retVal.rest= pointIt;
	return Iterator(retVal);
      }
    }
  }
  retVal.solidIt= objs.end();
  return Iterator(retVal);
}

// ##### first() #####################################################
void Solids::first() {
  current_obj.solidIt= objs.begin();
  if (exist(current_obj)) {
    current_obj.solidIt->points.first();
  }
}

// ##### getObjColor() ###############################################
Color Solids::getObjColor() throw (OutOfModelException*) {
  if (!hasObject()) { 
    throw new OutOfModelException();
  }
  return current_obj.solidIt->color;
}

// ##### getObject() #################################################
Element Solids::getObject() throw (OutOfModelException*) {
  if (!hasObject()) { 
    throw new OutOfModelException();
  }
  return *current_obj.rest.rest.faceIt;
}

// ##### getPosition() ###############################################
Solids::Iterator Solids::getPosition() {
  return Iterator(current_obj);
}

// ##### hasObject() #################################################
bool Solids::hasObject() {
  return exist(current_obj);
}

// ##### next() ######################################################
void Solids::next() throw (OutOfModelException*) {
  if (!hasObject()) {
    throw OutOfModelException();
  }

  current_obj.solidIt->points.next();
  if (current_obj.solidIt->points.hasObject()) {
    current_obj.rest= current_obj.solidIt->points.getPosition();
  } else {
    ++current_obj.solidIt;
    if (exist(current_obj)) {
      current_obj.solidIt->points.first();
      current_obj.rest= current_obj.solidIt->points.getPosition();
    }
  }
}

// ##### print() #####################################################
void Solids::print() {
  int solidNumber= 0;
  cerr << "solids::print()" << endl;
  for (ObjectContainer::iterator it= objs.begin(); it != objs.end(); ++it) {
    cout << "Körper " << solidNumber
	 << " (Farbe : " << it->color << ")" << endl;
    it->points.print();
  }
}

// ##### setPosition() ###############################################
void Solids::setPosition(Iterator position) {
  current_obj= position;
}

// ##### operator+= ##################################################
void Solids::operator+=(Solids addSolids) {
  addSolids.first();
  while (addSolids.hasObject()) {
    add(addSolids.getObject(), addSolids.getObjColor());
    addSolids.next();
  }
}

// EOF: src/cad/container/solids.cpp

/**
 * file: src/cad/container/faces.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/container/faces.h>
#include <cad/objects/plane.h>
#include <cad/objects/point.h>

#include <iostream>

// ##### equival() ###################################################
/**
 * Beschreiben obj1 und obj2 die gleiche Oberfläche?
 * @param obj1 Oberfläche 1
 * @param obj2 Oberfläche 2
 * @return \em true,  falls obj1 und obj2 den gleichen Datentyp
 *                    und die gleichen Begrenzungspunkte (in gleicher 
 *                      Reihenfolge) besitzen
 *         \em false, sonst
 * @pre obj1 != NULL and obj2 != NULL
 */
bool equival(Face* obj1, Face* obj2) {
  assert (obj1 != NULL && obj2 != NULL);

  if (obj1->getDataType() != obj2->getDataType()) {
    return false;
  }
  switch (obj1->getDataType()) {
  case CadObject::TRIANGLE:
  case CadObject::QUADRILATERAL:
    for (int corner= 0; corner < ((Plane *)obj1)->getCornerCount();
	 ++corner) {
      if (! ((*((Plane *)obj1))[corner] == (*((Plane *)obj2))[corner]) ) {
	return false;
      }
    }
    break;
  default:
    return false;
  }
  return true;
}

// ##### Faces() #####################################################
Faces::Faces() {
}

// ##### Faces() 
Faces::Faces(Face* object) {
  add(object);
}

// ##### ~Faces() ####################################################
Faces::~Faces() {
}

// ##### add() #######################################################
void Faces::add(Face* object) {
  assert (object != NULL);

  objs.insert(objs.begin(), object);
}

// ##### clear() #####################################################
void Faces::clear() {
  objs.clear();
}

// ##### count() #####################################################
unsigned Faces::count() {
  return objs.size();
}

// ##### empty() #####################################################
bool Faces::empty() {
  return objs.empty();
}

// ##### exist() #####################################################
bool Faces::exist(Face* object) {
  Iterator it= find(object);
  return exist(it);
}

// ##### exist() #####################################################
bool Faces::exist(Iterator it) {
  return it.faceIt != objs.end();
}

// ##### find() ######################################################
Faces::Iterator Faces::find(Face* object) {
  Iterator it;
  for (it.faceIt= objs.begin(); it.faceIt != objs.end(); ++it.faceIt) {
    if (equival(*it.faceIt, object)) {
      return Iterator(it);
    }
  }
  return Iterator(it);
}

// ##### first() #####################################################
void Faces::first() {
  current_object.faceIt= objs.begin();
}

// ##### getObject() #################################################
Element Faces::getObject() throw (OutOfModelException*) {
  if (!hasObject()) { 
    throw new OutOfModelException();
  }
  return *current_object.faceIt;
}

// ##### hasObject() #################################################
bool Faces::hasObject() {
  return exist(current_object);
}

// ##### next() ######################################################
void Faces::next() throw (OutOfModelException*) {
  if (!hasObject()) {
    throw new OutOfModelException();
  }
  ++current_object.faceIt;
}

// ##### print() #####################################################
void Faces::print() {
  first();
  while (hasObject()) {
    cout << "\t\t";
    getObject()->print();
    next();
  }
}

// EOF: src/cad/container/faces.cpp

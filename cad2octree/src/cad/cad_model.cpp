/**
 * file: src/cad/cad_model.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <cad/cad_model.h>

#include <iostream>

// ##### CadModel() ##################################################
CadModel::CadModel()
    : Faces(),
      maxPoint(MINIMUM_POSSIBLE_POINT), minPoint(MAXIMUM_POSSIBLE_POINT) {
}

// ##### add() #######################################################
void CadModel::add(Element object, Color color) {
  assert (object != NULL);

  Faces::add(object);
  objColor= color;
  maxPoint= object->max(maxPoint);
  minPoint= object->min(minPoint);
}

// ##### getMaxPoint() ###############################################
Point CadModel::getMaxPoint() {
  return maxPoint;
}

// ##### getMinPoint() ###############################################
Point CadModel::getMinPoint() {
  return minPoint;
}

// ##### getObjColor() ###############################################
Color CadModel::getObjColor() throw (OutOfModelException*) {
  return objColor;
}

// ##### print() #####################################################
void CadModel::print() {
  cout << "CAD-Model :";
  if (empty()) {
    cout << " leer." << endl;
    return;
  }

  cout << endl;
  Faces::print();
}

// EOF: src/cad/cad_model.cpp

/**
 * @file src/cad/objects/face.h
 * Definiert eine allgemeine abstrakte Fl�che als CadObject.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __FACE_H__
#define __FACE_H__

#include <cad/objects/cad_object.h>

/**
 * Allgemeine Klasse f�r Fl�chen.
 */
class Face : public CadObject {
 public:
  /**
   * Liefert zur�ck, wieviele Dimensionen die Fl�che besitzt.
   * @return 2
   */
  virtual int getDimension();

};

#endif // ! __FACE_H__

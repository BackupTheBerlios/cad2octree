/**
 * file: src/utils/options.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <options.h>

#include <stdlib.h>

// ##### Options() ###################################################
Options::Options() : alt_options(-1) {
}

// ##### getInstance() ###############################################
Options* Options::getInstance() {
  static Options* _options_class;

  if (_options_class == NULL) {
    _options_class= new Options();
  }
  return _options_class;
}

// ##### getOptions()#################################################
int Options::getOptions() {
  return alt_options;
}

// ##### setOptions()#################################################
void Options::setOptions(int options) {
  alt_options= options;
}

// EOF: src/utils/options.cpp

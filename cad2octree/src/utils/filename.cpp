/**
 * file: src/utils/filename.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <filename.h>

#include <string>
#include <iostream>

// ##### getExtension() ##############################################
const char* getExtension(const char* fileName) {
  const char* file= strdup(fileName);
  const char* ext= rindex(file, '.');

  if (ext == NULL) {
    return "";
  }

  return strdup(&(ext[1]));  // extension begins after '.'
}

// ##### getPurName() ################################################
const char* getPurName(const char* fileName) {
  string file= fileName;
  int ext= file.rfind('.');

  if (ext < 0) {
    return strdup(file.c_str());
  }

  return strdup(file.substr(0, ext).c_str());
}

// EOF: src/utils/filename.cpp

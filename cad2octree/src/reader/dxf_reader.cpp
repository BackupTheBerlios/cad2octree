/**
 * file: src/reader/dxf_reader.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <reader/dxf_reader.h>

#include <reader/dime_reader.h>

// ##### getFormatType() #############################################
const Reader::FormatType DxfReader::getFormatType() {
  return DXF;
}

// ##### getFormatName() #############################################
const char* DxfReader::getFormatName() {
  return "DXF";
}

// ##### readFile() ##################################################
/**
 * Es wird ein DimeReader initialisiert und zurückgeliefert.
 */
Reader* DxfReader::readFile(const char* fileName) 
    throw (ReadFileException*, FileFormatException*) {
  return new DimeReader(fileName);
}

// EOF: src/reader/dxf_reader.cpp

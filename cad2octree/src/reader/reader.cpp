/**
 * file: src/reader/reader.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <reader/reader.h>

#include <reader/dxf_reader.h>
#include <filename.h>

// ##### readFile() ##################################################
Reader* Reader::readFile(const char* fileName) 
    throw (ReadFileException*, FileFormatException*) {

  const char* ext= getExtension(fileName);

  if (!strcasecmp(ext, "dxf") || !strcasecmp(ext, "dxb")) {
    return DxfReader::readFile(fileName);
  }

  throw new FileFormatException
              (string(ext + (string)"-Format is not supported").c_str());
}

// EOF: src/reader/reader.cpp

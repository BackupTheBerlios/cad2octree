/**
 * file: src/writer/writer.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <writer/writer.h>

#include <writer/pot_writer.h>
#include <writer/xpm_writer.h>
#include <filename.h>

// ##### getWriter() #################################################
Writer* Writer::getWriter(const char* fileName) 
    throw (FileFormatException*) {
  const char* ext= getExtension(fileName);

  if (!strcasecmp(ext, "pot")) {
    return new PotWriter::PotWriter(fileName);
  }
  if (!strcasecmp(ext, "xpm")) {
    return new XpmWriter::XpmWriter(fileName);
  }

  throw new FileFormatException
              (string(ext + (string)"-Format is not supported").c_str());
}

// EOF: src/writer/writer.cpp

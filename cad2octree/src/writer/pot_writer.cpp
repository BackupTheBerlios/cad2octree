/**
 * file: src/writer/pot_writer.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <writer/pot_writer.h>

#define GROUND_DEPTH -1

// ##### PotWriter() #################################################
PotWriter::PotWriter(const char* fileName) : fileName(fileName) {
  wBinary= 0;
  wCount= 0;
}

// ##### ~PotWriter() ################################################
PotWriter::~PotWriter() {
  clear();
}

// ##### binWrite() ##################################################
void PotWriter::binWrite(Data data) {
  if (wCount >= 8*getCachSize()) {
    flushWrite();
  }
  wBinary = wBinary << 1;
  wBinary += data;
  ++wCount;
}

// ##### flushWrite() ################################################
void PotWriter::flushWrite() {
  while (wCount < 8*getCachSize()) {
    wBinary = wBinary << 1;
    ++wCount;
  }
  fwrite(&wBinary, getCachSize(), 1, potFile);
  wBinary = 0;
  wCount = 0;
}

// ##### getCachSize() ###############################################
const size_t PotWriter::getCachSize() {
  return sizeof(Data);
}

// ##### getFormatName() #############################################
const char* PotWriter::getFormatName() {
  return "POT";
}

// ##### getFormatType() #############################################
const Writer::FormatType PotWriter::getFormatType() {
  return POT;
}

// ##### writeFile() #################################################
void PotWriter::writeFile(IndexOct* tree)
    throw (WriteFileException*) {
  if (tree == NULL) {
    return;
  }
  setTree(tree->getTree());
  assert (getTree() != NULL);

  potFile = fopen(fileName, "w"); 
  if (potFile == NULL) {
    throw new WriteFileException(fileName);
  }

  fprintf(potFile, "%d\n", tree->getMaxTreeHight());
  writeTree(*getTree());
  flushWrite();
  fprintf(potFile, "\n");

  fclose(potFile);
}

// ##### writeInnerNode() ############################################
void PotWriter::writeInnerNode() {
  binWrite(INNER_NODE);
}

// ##### writeLeaf() #################################################
void PotWriter::writeLeaf(Color color) {
  assert (color >= NO_OBJECT);
  binWrite(LEAF);
  binWrite( (color == NO_OBJECT ? 0 : 1) );
}

// ##### writeTree() #################################################
void PotWriter::writeTree(Node node) {
  if (isLeaf(node)) {
    writeLeaf(node.flag);
    return;
  }
  writeInnerNode();
  for (PartType i= 0; i<OCT_PARTS; ++i) {
    writeTree(node.parts[i]);
  }
}

// EOF: src/writer/pot_writer.cpp

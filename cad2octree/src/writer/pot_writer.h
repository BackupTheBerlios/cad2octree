/**
 * @file src/writer/pot_writer.h
 * Konkreter Reader f�r Dateien im POT-Format.
 *
 * Es wird die Oktalbaumstruktur linearisiert in Pr�odertraversierung 
 * geschrieben.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __POT_WRITER_H__
#define __POT_WRITER_H__

#include <writer/writer.h>
#include <octree/oct_struct.h>

/**
 * Typ f�r zu schreibende Daten
 */
typedef unsigned int Data;

/**
 * Blattknoten.
 */
const Data LEAF= 0;

/**
 * Innerer Knoten.
 */
const Data INNER_NODE= 1;

/**
 * Konkreter Writer f�r das POT-Format.
 *
 * Es wird die Oktalbaumstruktur linearisiert in Pr�odertraversierung 
 * geschrieben.
 */
class PotWriter : public Writer, private OctStruct {
 public:
  /**
   * Konstruktor.
   * @param fileName Name der POT-Datei.
   */
  PotWriter(const char* fileName);

  /**
   * Destruktor.
   */
  virtual ~PotWriter();

  /**
   * Liefert den Namen Formats.
   * @return "POT"
   */
  virtual const char* getFormatName();

  /**
   * Liefert den Format-Typ.
   * @return Writer::POT
   */
  virtual const FormatType getFormatType();

  /**
   * Schreibt die Oktalbaumstruktur in die POT-Datei.
   *
   * Dazu wird der Oktalbaum linearisiert.
   * Die inneren Knoten und Bl�tter des Oktalbaumes werden dazu entsprechend
   * attributiert. Im Anschluss daran wird der Baum traversiert, d.h., 
   * nach dem Schema "Depth-First" (Tiefensuche) wird der Baum einmal 
   * durchlaufen und die Werte der innere Knoten bzw. Bl�tter werden 
   * bei ihrem ersten Besuch aufgeschrieben.
   * Als Ergebnis liegt der Baum in einem in der Ausgabedatei
   * geschriebenen Bin�rstrom vor.
   * @param tree zu schreibender Oktalbaum
   * @exception WriteFileException Dateischreibefehler
   */
  virtual void writeFile(IndexOct* tree)
    throw (WriteFileException*);

 private:
  /**
   * Bitweise Kodierung und Speicherung im Bin"arformat.
   *
   * Die Attribute NodeKind:LEAF bzw. NodeKind:INNER_NODE werden bitweise
   * kodiert und im Bin�rformat gespeichert. Am Ende der Ausgabe muss 
   * ein Flush durchgef"uhrt werden, wobei evtl. noch mit zus"atzlichen
   * Nullen aufgef"ullt wird.
   * @param data zu schreibendes Attribut
   */
  void binWrite(Data data);

  /**
   * Schreibt die gecachten Daten und leert den Cach.
   */
  void flushWrite();

  /**
   * Liefert die Cach-Gr��e.
   * @return Gr��e des Cachs
   */
  const size_t getCachSize();

  /**
   * Schreibt die Daten f�r den inneren Knoten.
   */
  void writeInnerNode();

  /**
   * Schreibt die Daten f�r den Blattknoten.
   * @param color Blattfarbe
   */
  void writeLeaf(Color color);

  /**
   * Schreibt den Unterbaum node in Preordertraversierung in die Ausgabedatei.
   * @param node Unterbaum
   */
  void writeTree(Node node);

// ##### Variablen ###################################################

  /**
   * Name der Ausgabedatei.
   */
  const char* fileName;

  /**
   * Handler f�r die Ausgabedatei.
   */
  FILE* potFile;

  /**
   * Anzahl gecachter Bits.
   */
  size_t wCount;

  /**
   * Gecachter Bin�rwert.
   */
  Data wBinary;
};

#endif // ! __POT_WRITER_H__

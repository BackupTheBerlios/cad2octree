/**
 * @file src/writer/pot_writer.h
 * Konkreter Reader für Dateien im POT-Format.
 *
 * Es wird die Oktalbaumstruktur linearisiert in Präodertraversierung 
 * geschrieben.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __POT_WRITER_H__
#define __POT_WRITER_H__

#include <writer/writer.h>
#include <octree/oct_struct.h>

/**
 * Typ für zu schreibende Daten
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
 * Konkreter Writer für das POT-Format.
 *
 * Es wird die Oktalbaumstruktur linearisiert in Präodertraversierung 
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
   * Die inneren Knoten und Blätter des Oktalbaumes werden dazu entsprechend
   * attributiert. Im Anschluss daran wird der Baum traversiert, d.h., 
   * nach dem Schema "Depth-First" (Tiefensuche) wird der Baum einmal 
   * durchlaufen und die Werte der innere Knoten bzw. Blätter werden 
   * bei ihrem ersten Besuch aufgeschrieben.
   * Als Ergebnis liegt der Baum in einem in der Ausgabedatei
   * geschriebenen Binärstrom vor.
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
   * kodiert und im Binärformat gespeichert. Am Ende der Ausgabe muss 
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
   * Liefert die Cach-Größe.
   * @return Größe des Cachs
   */
  const size_t getCachSize();

  /**
   * Schreibt die Daten für den inneren Knoten.
   */
  void writeInnerNode();

  /**
   * Schreibt die Daten für den Blattknoten.
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
   * Handler für die Ausgabedatei.
   */
  FILE* potFile;

  /**
   * Anzahl gecachter Bits.
   */
  size_t wCount;

  /**
   * Gecachter Binärwert.
   */
  Data wBinary;
};

#endif // ! __POT_WRITER_H__

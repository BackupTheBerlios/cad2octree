/**
 * @file src/reader/dxf_reader.h
 * Abstrakter Reader für Dateien im DXF-Format.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DXF_READER_H__
#define __DXF_READER_H__

#include <reader/reader.h>

/**
 * Abstrakter Reader für DXF-Dateien.
 *
 * Die Fabrikmethode readFile() erzeugt einen konkreten Reader für
 * DXF-Dateien unter Zuhilfename einer DXF-Importbibliothek,
 * getFormatName() und getFormatType() setzen diese Methoden
 * des Reader-Interface für \em DXF um.
 */
class DxfReader : public Reader {
 public:
  /**
   * Liefert den Formatnamen zurück.
   * @return "DXF"
   */
  virtual const char* getFormatName();

  /**
   * Liefert den Formattyp.
   * @return Reader::DXF
   */
  virtual const Reader::FormatType getFormatType();

  /**
   * Erzeugt den DxfReader für die Datei fileName.
   * @param fileName Name der Datei, aus der die Geometriedaten extrahiert 
   *          werden sollen. 
   * @return DxfReader zur Datei
   * @pre fileName spezifiziert eine gültige DXF-Datei.
   */
  static Reader* readFile(const char* fileName)
    throw (ReadFileException*, FileFormatException*);
}; // class DxfReader

#endif // ! DXF_READER_H

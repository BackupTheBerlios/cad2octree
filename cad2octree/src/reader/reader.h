/**
 * @file src/reader/reader.h
 * Fabrik-Methode und Reader-Interface zum Laden der Geometriedatei in das
 * CadModel.
 *
 * Zur Erzeugung des Readers kann die statische Methode \ref readFile()
 * verwendet werden.
 * Die restlichen Methoden definieren das Reader-Interface. Sie müssen
 * in allen verwendeten Readern implementiert werden.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __READER_H__
#define __READER_H__

#include <global.h>
#include <exception.h>
#include <cad/cad_model.h>

#include <stdio.h>

/**
 * Abstrakte Reader-Klasse.
 *
 * Definiert die abstrakten Methoden des Reader-Interfaces und
 * die statische Methode readFile(),
 * welche den Reader zu einer Datei zurückliefert.
 */
class Reader {
 public:
  // ##### Exceptions ################################################

  /**
   * Vaterklasse für alle von einem Reader geworfenen Exceptions
   */
  class ReaderException : public Exception {
  public:
    /** Default Exception-Konstruktor. */
    ReaderException() : Exception() {}
    /** Exception-Konstruktor. @param msg Fehlertext */
    ReaderException(string msg) : Exception(msg) {}
  };

  /**
   * Wird geworfen, wenn ein Lesefehler auftrat.
   */
  class ReadFileException : public ReaderException {
  public:
    /** Exception-Konstruktor. @param fileName Dateiname */
    ReadFileException(const char* fileName)
      : ReaderException("Error reading file " + (string)fileName) {}
  };

  /**
   * Wird geworfen, wenn Datei falsches Format besaß.
   */
  class FileFormatException : public ReaderException {
  public:
    /** Exception-Konstruktor. @param msg Fehlertext */
    FileFormatException(string msg) : ReaderException(msg) {}
  
    /** 
     * Exception-Konstruktor.
     * @param formatName Format-Name
     * @param fileName Dateiname
     * @param line Zeile, in der der Formatierungsfehler auftrat.
     */
    FileFormatException(const char* formatName, const char* fileName,
			int line) {
      char msg[STR_LEN];

      sprintf(msg, "%s-Format Error at line %d in File %s", 
	      formatName, line, fileName);
      message= msg;
    }
  };

  // ###### Reader ###################################################
  /**
   * Dateiformate, für welche es Reader gibt.
   */
  enum FormatType {DXF ///< Drawable Exchange Format 
  };
  
  /**
   * Fabrik-Methode: Erzeugt den Reader zur Datei fileName.
   *
   * Anhand der Dateierweiterung wird ein Reader für die Datei erzeugt.
   * Z.Z. wird das DXF-Format unterstützt.
   * Für Dateien mit der Erweiterung "dxf" bzw. "dxb" wird also
   * ein DxfReader unter Verwendung von DxfReader::readFile()
   * erzeugt.
   * Für alle anderen Formattypen wird eine FileFormatException
   * geworfen.
   * @param fileName Name der Datei, aus der die Geometriedaten extrahiert
   *        werden sollen.
   * @return Reader zur Datei
   * @exception ReadFileException Dateilesefehler
   * @exception FileFormatException Datei besitzt falsches Format.
   */
  static Reader* readFile(const char* fileName)
    throw (ReadFileException*, FileFormatException*);

  /**
   * Liefert das flächenorientierte CAD-Model zurück
   * @param color Farbe der Modell-Objekte
   * @param splitQuad Ob alle eingelesenen Vierecke als 2 Dreiecke im 
		      CadModel abgespeichert werden sollen. 
   * @return CadModel
   */
  virtual CadModel* getCadModel(Color color, bool splitQuad)= 0;

  /**
   * Liefert Name und Version der zum Einlesen verwendeten Hilfsbibliothek
   * zurück. Z.B. "Dime Version 0.9".
   * @return Bibliotheksname und -version
   */
  virtual const char* getLibVersion()= 0;

  /**
   * Liefert die in der Datei eingetragene Formatversion. Falls
   * diese von der Import-Bibliothek extrahiert werden kann und
   * ansonsten "unknown".
   * @return extrahierte Formatversion
   */
  virtual const char* getFileFormatVersion()= 0;

  /**
   * Liefert den Namen Formats. Z.B. "DXF" für einen DxfReader.
   * @return Formatnamen
   */
  virtual const char* getFormatName()= 0;

  /**
   * Liefert den Format-Typ. Z.B. FormatType::DXF für einen DxfReader.
   * @return Format-Typ
   */
  virtual const FormatType getFormatType()= 0;

  /**
   * Gibt Geometriedaten aus.
   *
   * Gibt die Geometriedaten, die der Reader extrahiert und in seinem internen
   * Model gespeichert hat auf der Konsole aus.
   */
  virtual void print()= 0;

}; // class Reader

#endif // ! READER_H

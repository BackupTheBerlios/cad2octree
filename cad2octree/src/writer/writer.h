/**
 * @file src/writer/writer.h
 * Fabrik-Methode und Writer-Interface zum Schreiben der Oktalbaumdatei.
 *
 * Zur Erzeugung des Writers kann die statische Methode \ref getWriter()
 * verwendet werden.
 * Die restlichen Methoden definieren das Writer-Interface. Sie müssen
 * in allen verwendeten Writern implementiert werden.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __WRITER_H__
#define __WRITER_H__

#include <exception.h>
#include <octree/index_oct.h>

#include <stdio.h>

/**
 * Abstrakte Writer-Klasse.
 *
 * Definiert die abstrakten Methoden des Writer-Interfaces und
 * die statische Methode getWriter(),
 * welche den Writer zu einer Datei zurückliefert.
 */
class Writer {
 public:
  // ##### Exceptions ################################################

  /**
   * Vaterklasse für alle von einem Writer geworfenen Exceptions
   */
  class WriterException : public Exception {
  public:
    /** Default Exception-Konstruktor. */
    WriterException() : Exception() {}
    /** Exception-Konstruktor. @param msg Fehlertext */
    WriterException(string msg) : Exception(msg) {}
  };

  /**
   * Wird geworfen, wenn ein Schreibfehler auftrat.
   */
  class WriteFileException : public WriterException {
  public:
    /** Exception-Konstruktor. @param fileName Dateiname */
    WriteFileException(const char* fileName)
      : WriterException("Error writing file " + (string)fileName) {}
  };

  /**
   * Wird geworfen, wenn Datei falsches Format besaß.
   */
  class FileFormatException : public WriterException {
  public:
    /** Exception-Konstruktor. @param msg Fehlertext */
    FileFormatException(string msg) : WriterException(msg) {}
  };

  // ###### Writer ###################################################
  /**
   * Dateiformate, für welche es Writer gibt.
   */
  enum FormatType {POT, ///< Preorder Traversing Octree-Structure 
                   XPM  ///< X11 Pixmap Format
  };
  
  /**
   * Fabrik-Methode: Erzeugt den Reader zur Datei fileName.
   *
   * Anhand der Dateierweiterung wird ein Writer für die Datei erzeugt.
   * Z.Z. wird das POT-Format und das XPM-Format unterstützt.
   * Für Dateien mit der Erweiterung "pot" wird also
   * ein PotWriter erzeugt.
   * Für alle anderen Formattypen wird eine FileFormatException
   * geworfen.
   * @param fileName Name der Datei, in die das Oktalbaum-Modell gespeichert
   *        werden soll.
   * @return Writer zur Datei
   * @exception FileFormatException Datei besitzt falsches Format.
   */
  static Writer* getWriter(const char* fileName)
    throw (FileFormatException*);

  /**
   * Liefert den Namen Formats. Z.B. "POT" für einen PotWriter.
   * @return Formatnamen
   */
  virtual const char* getFormatName()= 0;

  /**
   * Liefert den Format-Typ. Z.B. FormatType::POT für einen PotWriter.
   * @return Format-Typ
   */
  virtual const FormatType getFormatType()= 0;

  /**
   * Schreibt die Oktalbaumstruktur in die Datei.
   * @param tree zu schreibende Oktalbaum-Struktur
   * @exception WriteFileException Dateischreibefehler
   */
  virtual void writeFile(IndexOct* tree)
    throw (WriteFileException*) = 0;

}; // class Writer

#endif // ! WRITER_H

/**
 * @file src/writer/xpm_writer.h
 * Konkreter Reader für Dateien im XPM-Format.
 *
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __XPM_WRITER_H__
#define __XPM_WRITER_H__

#include <writer/writer.h>
#include <octree/index_oct.h>

#include <fstream>

/**
 * Konkreter Writer für das XPM-Format.
 *
 */
class XpmWriter : public Writer {
 public:
  /**
   * Konstruktor.
   * @param fileName Namensstamm der XPM-Datei.
   */
  XpmWriter(const char* fileName);

  /**
   * Destruktor.
   */
  virtual ~XpmWriter();

  /**
   * Liefert den Namen Formats.
   * @return "XPM"
   */
  virtual const char* getFormatName();

  /**
   * Liefert den Format-Typ.
   * @return Writer::XPM
   */
  virtual const FormatType getFormatType();

  /**
   * Schreibt "Schnitte durch die Oktalbaumstruktur" in XPM-Dateien.
   *
   * 
   * @param tree zu verwendeter Oktalbaum
   * @exception WriteFileException Dateischreibefehler
   * @pre DIMENSIONS == 3
   */
  void writeFile(IndexOct* tree)
    throw (WriteFileException*);

 private:
  /**
   * Liefert das Farbzeichen.
   * @param h Koordinate der Schnittachse
   * @param i Koordinaten der anderen beiden Schnittachse
   * @return Farbcode der Normzelle (h; i)
   */
  char getColorChar(AxIndex h, AxIndex i[2]);
  
  /**
   * Liefert den vollständigen Namen der zu schreibenden Datei mit der Nummer
   * number. Der Dateiname wird wiefolgt gebildet:\n
   *   \t <Namenstamm der Ausgabedatei>_<number>.<Dateierweiterung>
   * @param number Lfd. Nr.; entspricht Höhenzahl der Schnittachse
   */
  const char* getFileName(int number);

  /**
   * Liefert die Breite der zu schreibenden XPM-Datei. Entspricht der Anzahl
   * der unterliegenden Normzellen in eine Achsrichtung des Oktalbaums auf
   * tiefster Ebene.
   * @return Bild-Breite
   */
  AxIndex getWidth();

  /**
   * Schreibt den Farbcode colorChar in die Ausgabedatei.
   * @param colorChar zu schreibender Farbcode
   */
  void write(char colorChar);
 
  /**
   * Schreibt den Teil der XPM-Datei, der sich hinter der Voxeltabelle 
   * befindet.
   */
  void writeFooter();

  /**
   * Schreibt den Dateikopf. Dies umfasst den Teil bis zur Voxeltablle, also
   * XPM-Kennung und Farbdefinitionen.
   * @param number Dagteinummer; entspricht Höhenzahl der Schnittachse
   */
  void writeHeader(int number);
  
  /**
   * Schreibt den Zeilenanfang.
   */
  void writeLineBegin();
  
  /**
   * Schreibt das Zeilenende.
   * @param isLast Ob es die letzte Voxelzeile ist.
   */
  void writeLineEnd(bool isLast);
 
// ##### Variablen ###################################################

  /**
   * Verwendete Dateierweiterung.
   */
  const char* extension;
  
  /**
   * Namenstamm der Ausgabedatei ohne Erweiterung.
   */
  const char* fileName;

  /**
   * Oktalbaum.
   */
  IndexOct* octree;

  /**
   * Ausgabestream.
   */
  ofstream out;

  /**
   * Achse, entlang welcher die Schnitte erfolgen.
   */
  Axis sectAxis;

};

#endif // ! __XPM_WRITER_H__

/**
 * @file src/reader/dime_reader.h
 * Konkreter Reader für Dateien im DXF-Format. Es wird \em DIME
 * zum DXF-Import verwendet.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DIME_READER_H__
#define __DIME_READER_H__

#include <reader/dxf_reader.h>
#include <reader/dime_help.h>

#include <dime/Model.h>
#include <dime/entities/Entity.h>

/**
 * Konkreter Reader für das DXF-Format. Zur Implementierung
 * der Methoden des Reader-Interface wird die DIME-Bibliothek verwendet.
 */
class DimeReader : public DxfReader {
 public:
  /**
   * Konstruktor.
   * @param dxfFile Name der DXF-Datei.
   * @exception ReadFileException Lesefehler
   * @exception FileFormatException Datei dxfFile besitzt nicht das DXF-Format
   */
  DimeReader(const char* dxfFile)
    throw (ReadFileException*, FileFormatException*);

  /**
   * Destruktor.
   */
  virtual ~DimeReader();

  virtual CadModel* getCadModel(Color color, bool splitQuad);
  virtual const char* getFileFormatVersion();

  /**
   * Liefert die DIME-Version.
   * @return DIME-Version
   */
  virtual const char* getLibVersion();

  virtual void print();

 private:
  /**
   * Konvertiert den Inhalt eines Records param unter Berücksichtigung
   * des Gruppen-Codes groupCode des Records in einen char-String.
   * @param param Inhalt des Records
   * @param groupCode der Gruppen-Code des Records (definiert das Format
   *          von param)
   * @return Inhalt des Records als char-String
   */
  static const char* dimeParam2str(dimeParam param, int groupCode);

  /**
   * Fügt die aus entity extrahierten Geometridaten zu dem CadModel
   * data hinzu. 
   *
   * (Callback-Routine: Wird von dimeModel::traverseEntity() in getCadModel()
   * verwendet.)
   * @param state dime-interner Parameter
   * @param entity die Entity
   * @param data CadModel, in das entity eingefügt werden soll
   * @return true, entity != NULL\n
   * @pre data != NULL
   */
  static bool generateCadModel(const dimeState* const state,
			       dimeEntity *entity, void *data);

  /**
   * Gibt die Entity aus der Konsole aus.
   *
   * (Callback-Routine: Wird von dimeModel::traverseEntity() in print() 
   * verwendet.)
   * @param state dime-interner Parameter
   * @param entity die Entity
   * @param data wird nicht verwendet (aber Bestandteil der Definition)
   * @return true,  entity != NULL\n
   *         false, sonst
   */
  static bool printEntity(const dimeState* const state,
  			  dimeEntity *entity, void *data);

  /**
   * Liefert das interne Model der aus der DXF-Datei eingelesenen
   * Daten
   * @return internes Model
   * @pre das interne Model wurde erzeugt (geschieht im Konstruktor
   *      und sollte eigentlich immer der Fall sein :-)
   */
  dimeModel* getDimeModel();

  /**
   * aus dem dimeModel zu erstellendes CadModel
   * @see getCadModel()
   * @see generateCadModel()
   */
  CadModel* cadModel;

  /**
   * Farbe mit der alle Objekte des zu erzeugenden CadModel
   * eingefärbt werden sollen
   * @see getCadModel()
   * @see generateCadModel()
   */
  Color color;

  /**
   * Internes Model. Wird beim Einlesen der DXF-Datei von Dime erzeugt
   * und zum extrahieren der CAD-Information verwendet.
   */
  dimeModel* model;

}; // class DimeReader

#endif // ! __DIME_READER_H__

/**
 * @file src/utils/filename.h
 * Funktionen zum Umgang mit Dateinamen
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __FILENAME_H__
#define __FILENAME_H__

/**
 * Liefert die Dateierweiterung zu einer Datei.
 * @param fileName Dateiname
 * @return Dateierweitrung
 */
const char* getExtension(const char* fileName);

/**
 * Liefert den Dateinamen ohne Erweiterung
 */
const char* getPurName(const char* fileName);


#endif // ! __FILENAME_H__

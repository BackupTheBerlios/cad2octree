/**
 * @file src/utils/exception.h
 * Allgemeine Ausnahme.
 *
 * Basisklasse für alle definierten Exception-Klassen.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <global.h>

#include <string>

/**
 * Vaterklasse für alle geworfenen Exceptions
 */
class Exception {
 public:
  /** Default-Konstruktor. */
  Exception() {}

  /** Exception-Konstruktor. @param msg Fehlertext */
  Exception(string msg) : message(msg) { }

  /**
   * Gibt die Fehlermeldung zur Ausname zurück
   * @return Fehlerbeschreibung
   */
  const char* getMsg() {
    return message.c_str();
  }

 protected:
  /** Fehlertext */
  string message;
};

/**
 * Konnte nicht genügend Abreitsspeicher allozieren.
 */
class NotEnoughMemoryException : public Exception {
 public:
  /**
   * Exception-Konstruktor.
   */
  NotEnoughMemoryException() : Exception("Not enough memory") {}
};

#endif // ! __EXCEPTION_H__

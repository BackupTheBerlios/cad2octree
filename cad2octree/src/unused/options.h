/**
 * @file src/utils/options.h
 * Optionsklasse.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __OPTIONS_H__
#define __OPTIONS_H__

/**
 * Options-Klasse.
 * Singleton.
 */
class Options {
 public:
  static Options* getInstance();

  /**
   * Liefert die Optionen.
   * @return Optionsschalter
   */
  int getOptions();

  /**
   * Setzt die Optionen.
   * @param options Optionsschalter
   */
  void setOptions(int options);

 protected:
  /**
   * Konsrtuktor.
   */
  Options();

 private:
  /**
   * zu verwendender Algorithmus.
   * -1 Schraffieren
   *  0 isIn angle / isPlane det
   *  1 isIn angle / isPlane Footpoint
   */
  int alt_options;

  /**
   * Referenz auf die Options-Klasse.
   */
  // static Options* _options_class;
};

#endif // ! __OPTIONS_H__

/**
 * @file src/utils/timer.h
 * Zeitmesser.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <sys/time.h>

/**
 * Sekunden pro Tag
 */
#define SEC_PER_DAY 24*60*60

/**
 * Mikrosekunden pro Sekunde
 */
#define USEC_PER_SEC 1000*1000

/**
 * Zeitmesser.
 */
class Timer {
 public:
  /**
   * Konstruktor.
   * Setzt die Stoppuhr zur�ck.
   */
  Timer();

  /**
   * Liefert die abgelaufene Zeit. (Seit der Initialisierung bzw. seit dem
   * letzten Reset in Sekunden)
   * @return Zeit / sec
   */
  float getTime();

  /**
   * Liefert die abgelaufene Zeit als Textstring.
   * @return abgelaufene Zeit
   * @see getTime()
   */
  const char* getTimeStr();

  /**
   * Gibt die abgelaufene Zeit aus und setzt die Stoppuhr zur�ck.
   */
  void print();

  /**
   * Setzt due Stoppuhr zur�ck.
   */
  void reset();

  /**
   * Wandelt die Zahl num in eine Zeichenkette um. Dabei gibt maxNum an,
   * ab welcher Zahl es ein �berschlag gibt. Der R�ckgabestring wird
   * mit soviel 0-en aufgef�llt, dass sich eine maxNum-1 -stellige Zahl
   * ergibt. So liefert z.B. toStr(65, 60) <tt>05</tt> oder 
   * toStr(111, 100) <tt>11</tt>.
   * @param num zu konvertierende Zahl
   * @param maxNum Einheitengr��e. Modulo dieser Zahl wird num betrachtet.
   * @return num als Zeichenkette in entsprechender Formatierung.
   */
  char* toStr(long num, long maxNum);

 private:
  /**
   * Restzeit.
   */
  struct itimerval time;

};

#endif // ! __TIMER_H__

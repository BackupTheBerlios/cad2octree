/**
 * @file src/generator/scan_line.h
 * Zum 'Linienziehen Über NodeIndex' (vgl. Besenham)
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __SCAN_LINE_H__
#define __SCAN_LINE_H__

#include <node_vec.h>

/**
 * Klasse zum Berechnen des 'Nachfolgepunktes' einer Line auf NodeIndex-Basis.
 */
class ScanLine {
 public:
  /**
   * Konstruktor.
   * @param start Anfangspunkt der Linie
   * @param end Endpunkt der Linie
   * qpre start.getHight() = end.getHight()
   */
  ScanLine(NodeIndex start, NodeIndex end);

  /**
   * Liefert den aktuellen Linienpunkt
   * @return aktueller Index der Linie 
   */
  NodeIndex getCurrent();

  /**
   * Ob der Endpunkt noch nicht erreicht ist.
   * @return ('interner aktueller Punkt') != Endunkt 
   */
  bool hasNext();

  /**
   * Geht zum nächsten Linienpunkt.
   */
  void next();

 private:
#ifndef COMB_SCAN_LINE
  /**
   * Liefert den absoluten Fehler zur Ideallinie, wenn zum nächsten Punkt 
   * entlang der Achse testAx gegangen wird.
   * @param testAx Achse 
   * @return Absoluter Fehler 
   */
  AxIndex getError(Axis testAx);
#else

  /**
   * Liefert den absoluten Fehler zur Ideallinie, wenn zum nächsten Punkt 
   * entlang der Achs-Kombination testAxComb gegangen wird.
   * @param testAxComb Achsen-Kombination 
   * @return Absoluter Fehler 
   */
  AxIndex getErrorComb(AxComb testAxComb);
#endif

#ifndef COMB_SCAN_LINE
  /**
   * Liefert den Fehlervektor, wenn auf der Achse testAx weitergegangen wird. 
   * @param testAx Achse 
   * @return Fehlervektor 
   */
  NodeIndex getErrorVec(Axis testAx);
#else
  /**
   * Liefert den Fehlervektor, wenn auf der Achs-Kombination testAxComb 
   * weitergegangen wird. 
   * @param testAxComb Achsen-Kombination 
   * @return Fehlervektor 
   */
  NodeIndex getErrorCombVec(AxComb testAxComb);
#endif

#ifndef COMB_SCAN_LINE
  /**
   * Nachbarpunkt in ax-Richtung
   * @param ax Achse 
   */
  NodeIndex getNext(Axis ax);
#else
  /**
   * Nachbarpunkt in axComb-Richtung
   * @param axComb Achsen-Kombination 
   */
  NodeIndex getNextComb(AxComb axComb);
#endif

  /**
   * Liefert die maximale Komponente des Fehlervektors testError.
   * @param testError Fehlervektor
   * @return maximale Komponente
   */
  AxIndex maxError(NodeIndex testError);

  /**
   * Liefert die minimale Komponente des Fehlervektors testError.
   * @param testError Fehlervektor
   * @return minmale Komponente
   */
  AxIndex minError(NodeIndex testError);

#ifndef COMB_SCAN_LINE
  /**
   * Passt das interne Fehlerregister an.
   */
  void refreshError(Axis stepAx);
#else
  /**
   * Passt das interne Fehlerregister an.
   */
  void refreshErrorComb(AxComb stepAxComb);
#endif

  /**
   * Aktuelle Scan-Position
   */
  NodeIndex current; 
  
  /**
   * Richtung der Linie
   */
  NodeIndex dir;
  
  /**
   * Linien-Endpunkt
   */
  NodeIndex end;
  
  /**
   * Fehlervektor
   */
  NodeIndex error;
};

#endif // ! __SCAN_LINE_H__

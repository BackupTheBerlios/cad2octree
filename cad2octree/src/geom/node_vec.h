/**
 * @file src/geom/node_vec.h
 * Definiert Vektoren zwischen 'indizierten' Oktalbaumknoten.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __NODE_VEC_H__
#define __NODE_VEC_H__

#include <node_index.h>

/**
 * 0-Vektor.
 */
#define NULL_NODE_VEC NodeIndex(0, 0, 0)

/**
 * Richtungstyp für gesamten Vektor.
 */
typedef NodeIndex Direction;

/**
 * Klasse für Vektoren zwischen Oktalbaumknoten.
 *
 * Hierfür wird NodeIndex um weitere Operationen erweitert.
 */
class NodeVec : public NodeIndex {
 public:
  /**
   * Default-Konstruktor.
   * Erzeugt den NodeVec zum NodeIndex nodeIdx.
   * @param nodeIdx Index des Oktalbaumknotens
   */
  NodeVec(NodeIndex nodeIdx);

  /**
   * Konstruktor.
   * Erzeugt den NodeVec, der den Vektor
   * \f$\over{\mbox{pStart}\ \mbox{pEnd}}\f$ darstellt.
   * @param pStart Quellknoten
   * @param pEnd Zielknoten
   * @pre pStart.getHight() = pEnde.getHight()
   */
  NodeVec(NodeVec pStart, NodeVec pEnd);

  /**
   * Liefert, die Richtung, in die der Knotenvektor zeigt.
   * Für jede Raumrichtung wird ermittelt, ob der Quellknoten vor (+1),
   * hinter (-1) oder auf gleicher Höhe (0) wie der Zielknoten liegt.
   * Sie ergibt sich aus den Vorzeichen der jeweiligen Achsen-Idizes.
   * @return Richtung des Knotenvektors
   */
  Direction getDirection();

};

/**
 * Liefert den resultierenden Differenzvektor.
 * @param p1 erster Knotenvektor
 * @param p2 zweiter Knotenvektor
 * @return p1-p2
 * @pre p1.getHight() = p2.getHight()
 */
NodeVec operator-(NodeVec p1, NodeVec p2);

#endif // ! __NODE_VEC_H__

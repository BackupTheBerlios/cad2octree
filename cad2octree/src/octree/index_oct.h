/**
 * @file src/octree/index_oct.h
 * 'Indizierter' Oktalbaum.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __INDEX_OCT_H__
#define __INDEX_OCT_H__

#include <octree/oct_struct.h>
#include <node_index.h>
#include <polygon.h>

#include <exception.h>

/**
 * Zahl der Unterpartitionierungen pro Achse
 */
const Axis AXIS_PARTS = 2;

/**
 * 'Indizierter' Oktalbaum.
 *
 * Stellt Operationen für die Oktalbaumbearbeitung zur Verfügung, wobei
 * die Knoten der Oktalbaumstruktur über den \em Knotenindex referenziert
 * werden.
 */
class IndexOct : public OctStruct {
 public:
  /**
   * Default-Konstrukor.
   * @param maxTreeHight maximale Baumhöhe
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   */
  IndexOct(Hight maxTreeHight) throw(NotEnoughMemoryException*);

  /**
   * Fügt den neuen Knoten mit dem Index p und der Farbe color zur
   * Oktalbaumstruktur hinzu. 
   * @param p Knotenindex
   * @param color Knotenfarbe
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   * @pre 0 <= p.getHight() <= getMaxTreeHight()
   */
  void add(NodeIndex p, Color color) throw (NotEnoughMemoryException*);

  /**
   * Fügt die Oberfläche s mit der Farbe color in den Oktalbaum ein.
   * @param s Oberfläche
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              neue Oktalbaumstrukturteile zu allozieren. 
   * @pre s != NULL
   * @pre s.getHight() = BASE_NODE_HIGHT
   */
  void add(Surface* s, Color color) throw (NotEnoughMemoryException*);

  /**
   * Befindet sich der Knoten mit Index p im Oktalbaum?
   * @param p Knotenindex
   * @return p referenziert den Wurzelknoten oder
   *           ( es existiert der Vater von p und dann
   *             ist p's Vater kein Blatt)
   */
  bool exist(NodeIndex p);

  /**
   * Liefert den Index des i-ten Unterknotens.
   * @param parent Eltern-Index
   * @param i Nr. der Unterpartition
   * @return i-ter Kindsindex
   * @pre parent.getHight() != BASE_NODE_HIGHT and isIn(parent)
   */
  NodeIndex getChild(NodeIndex parent, PartType i);

  /**
   * Liefert die Knotenfarbe. p darf keinen inneren Knoten referenzieren.
   * Falls p nicht existiert, liefert es getColor seines 'virtuellen'
   * Vaters.
   * @param p Knotenindex
   * @pre isLeaf(p') mit p' tiefster existierender Vater (incl. p)
   */
  Color getColor(NodeIndex p);

  /**
   * Falls p der Index eines existierenden Knotens ist,
   * liefert es p, ansonsten den tiefsten existierenden
   * Vater.
   * @param p Knotenindex
   * @return tiefster existierender Vater (wobei p selbst als Vater von p
   *           zählt)
   * @post getExistNode(p).getHight() >= p.getHight()
   */
  NodeIndex getExistNode(NodeIndex p);

  /**
   * Liefert die maximale Baumhöhe.
   * @return maximale Baumhöhe
   */
  Hight getMaxTreeHight();

  /**
   * Liefert den Offset, der aus der Unterpartionsnummer und der Achsnummer
   * resultiert.
   * @param partNumber Nummer der Unterpartition
   * @param axis Nummer der Index-Achse
   * @return \f$ ( \mbox{partNumber} \triangleleft \mbox{axis} )
   *               \bmod \mbox{AXIS\_PARTS} \f$
   */
  static AxIndex getPartOfs(PartType partNumber, Axis axis);

  /**
   * Ist p Blattknoten. p muss existieren.
   * @param p Knotenindex
   * @return Ob p Blattknoten ist.
   * @pre exist(p)
   */
  bool isLeaf(NodeIndex p);

  /**
   * Kann sich p innerhalb des Oktalbaumes befinden, wenn der Oktalbaum
   * vollständig besetzt ist (alle Blätter befinden sich auf der Höhe
   * BASE_NODE_HIGHT) ?
   * @param p Knoten-Index
   * @return \f$ \forall_{i} \in [0;\dim) :
   *                0 <= p[i] < 1 \triangleright \mbox{getMaxTreeHight} \f$
   */
  bool isIn(NodeIndex p);

  /**
   * Setzt die Knotenfarbe. p darf keinen inneren Knoten referenzieren.
   * Falls p nicht existiert, führt es setColor seines 'virtuellen'
   * Vaters aus.
   * @param p Knotenindex
   * @param color neue Knotenfarbe
   * @pre isLeaf(p')
   */
  void setColor(NodeIndex p, Color color);

 protected:
  /**
   * Falls p der Index eines existierenden Knotens ist,
   * liefert es p.getHight(), ansonsten die Höhe des tiefsten existierenden
   * Vaters. node enthält den entsprechenden Knoten.
   * @param p Knotenindex
   * @param subtree Zeiger auf den existierenden Knoten
   * @return Asthöhe
   * @post getExistNode(p, node) >= p.getHight()
   * @post octree != NULL
   */
  Hight getExistNode(NodeIndex p, _octree &subtree);
  
  /**
   * Befindet sich der Knoten mit dem Index p nicht unterhalb der Höhe h?
   * @param p Knoten-Index
   * @param h Vergleichshöhe
   * @return p.getHight() >= h
   * \note Ist h die minimale Blatthöhe des Astes auf dem p liegt, liefert
   * \em isIn(p, h), ob p existiert.
   */
  bool isIn(NodeIndex p, Hight h);

#ifdef MARK_BORDER
  /**
   * Setzt p als Randknoten mit der Normfarbe color
   * @param p Blattknotenindex
   * @param color Normfarbe
   * @pre isLeaf(p)
   * @pre color >= NO_OBJECT
   */
  void setBorderColor(NodeIndex p, Color color);
#endif

 private:
  /**
   * Fügt die Knoten, die sich auf der Oberfläche s
   * befinden, mit der Farbe color in den Oktalteilbaum subtree ein.
   * myIdx entspricht den Index des Wurzelknotens des Teilbaums.
   *       myIdx wird benötigt, um zu erkennen inwieweit subtree für
   *       das Hinzufügen der Oberfläche überhaupt relevant ist.
   * @param parent Oktalteilbaum
   * @param myIdx Index des Wurzelknotens des Oktalteilbaums
   * @param s Surface
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              neue Oktalbaumstrukturteile zu allozieren.
   * @pre isIn(myIdx) 
   * @pre s != NULL
   */
  void add(_octree parent, NodeIndex myIdx, Surface* s, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * Liefert die Unterpartition einer Achse für den Knoten auf dem Ast
   * an der Höhe h.
   * @param idx Achs-Index des Knotens
   * @param h Höhe der zubetrachtenden Stelle des Astes
   * @return Unterpartion für die Achse an der Stelle h
   */
  PartType getPart(AxIndex idx, Hight h);

  /**
   * Liefert die Unterpartition für den Knoten auf dem Ast
   * an der Höhe h.
   * @param p Knotenindex
   * @param h Höhe der zubetrachtenden Stelle des Astes
   * @return Unterpartion an der Stelle h
   */
  PartType getPart(NodeIndex p, Hight h);

  /**
   * Höhe des Wurzelknotens. Ist mit der Maximalhöhe des Baums identisch.
   */
  Hight rootHight;
};

#endif // ! __INDEX_OCT_H__

/**
 * @file src/octree/index_oct.h
 * 'Indizierter' Oktalbaum.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
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
 * Stellt Operationen f�r die Oktalbaumbearbeitung zur Verf�gung, wobei
 * die Knoten der Oktalbaumstruktur �ber den \em Knotenindex referenziert
 * werden.
 */
class IndexOct : public OctStruct {
 public:
  /**
   * Default-Konstrukor.
   * @param maxTreeHight maximale Baumh�he
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   */
  IndexOct(Hight maxTreeHight) throw(NotEnoughMemoryException*);

  /**
   * F�gt den neuen Knoten mit dem Index p und der Farbe color zur
   * Oktalbaumstruktur hinzu. 
   * @param p Knotenindex
   * @param color Knotenfarbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   * @pre 0 <= p.getHight() <= getMaxTreeHight()
   */
  void add(NodeIndex p, Color color) throw (NotEnoughMemoryException*);

  /**
   * F�gt die Oberfl�che s mit der Farbe color in den Oktalbaum ein.
   * @param s Oberfl�che
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
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
   *           z�hlt)
   * @post getExistNode(p).getHight() >= p.getHight()
   */
  NodeIndex getExistNode(NodeIndex p);

  /**
   * Liefert die maximale Baumh�he.
   * @return maximale Baumh�he
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
   * vollst�ndig besetzt ist (alle Bl�tter befinden sich auf der H�he
   * BASE_NODE_HIGHT) ?
   * @param p Knoten-Index
   * @return \f$ \forall_{i} \in [0;\dim) :
   *                0 <= p[i] < 1 \triangleright \mbox{getMaxTreeHight} \f$
   */
  bool isIn(NodeIndex p);

  /**
   * Setzt die Knotenfarbe. p darf keinen inneren Knoten referenzieren.
   * Falls p nicht existiert, f�hrt es setColor seines 'virtuellen'
   * Vaters aus.
   * @param p Knotenindex
   * @param color neue Knotenfarbe
   * @pre isLeaf(p')
   */
  void setColor(NodeIndex p, Color color);

 protected:
  /**
   * Falls p der Index eines existierenden Knotens ist,
   * liefert es p.getHight(), ansonsten die H�he des tiefsten existierenden
   * Vaters. node enth�lt den entsprechenden Knoten.
   * @param p Knotenindex
   * @param subtree Zeiger auf den existierenden Knoten
   * @return Asth�he
   * @post getExistNode(p, node) >= p.getHight()
   * @post octree != NULL
   */
  Hight getExistNode(NodeIndex p, _octree &subtree);
  
  /**
   * Befindet sich der Knoten mit dem Index p nicht unterhalb der H�he h?
   * @param p Knoten-Index
   * @param h Vergleichsh�he
   * @return p.getHight() >= h
   * \note Ist h die minimale Blatth�he des Astes auf dem p liegt, liefert
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
   * F�gt die Knoten, die sich auf der Oberfl�che s
   * befinden, mit der Farbe color in den Oktalteilbaum subtree ein.
   * myIdx entspricht den Index des Wurzelknotens des Teilbaums.
   *       myIdx wird ben�tigt, um zu erkennen inwieweit subtree f�r
   *       das Hinzuf�gen der Oberfl�che �berhaupt relevant ist.
   * @param parent Oktalteilbaum
   * @param myIdx Index des Wurzelknotens des Oktalteilbaums
   * @param s Surface
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              neue Oktalbaumstrukturteile zu allozieren.
   * @pre isIn(myIdx) 
   * @pre s != NULL
   */
  void add(_octree parent, NodeIndex myIdx, Surface* s, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * Liefert die Unterpartition einer Achse f�r den Knoten auf dem Ast
   * an der H�he h.
   * @param idx Achs-Index des Knotens
   * @param h H�he der zubetrachtenden Stelle des Astes
   * @return Unterpartion f�r die Achse an der Stelle h
   */
  PartType getPart(AxIndex idx, Hight h);

  /**
   * Liefert die Unterpartition f�r den Knoten auf dem Ast
   * an der H�he h.
   * @param p Knotenindex
   * @param h H�he der zubetrachtenden Stelle des Astes
   * @return Unterpartion an der Stelle h
   */
  PartType getPart(NodeIndex p, Hight h);

  /**
   * H�he des Wurzelknotens. Ist mit der Maximalh�he des Baums identisch.
   */
  Hight rootHight;
};

#endif // ! __INDEX_OCT_H__

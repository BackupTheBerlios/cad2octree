/**
 * @file src/octree/oct_struct.h
 * Oktalbaumstruktur.
 *
 * Unterste Schicht.
 * Stellt Low-Level-Operationen für die Oktalbaumsturktur zur Verfügung.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __OCT_STRUCT_H__
#define __OCT_STRUCT_H__

#include <global.h>
#include <exception.h>

/**
 * Typ für Partitionen.
 */
typedef int PartType;

/**
 * Anzahl der Oktagon-Partitionen. Entspricht der Zahl der Kinder eines
 * inneren Knotens im Oktalbaum.
 */
const PartType OCT_PARTS = 1 << DIMENSIONS;

/**
 * Knotenattributstyp. Definiert für Blätter die Farbe des Körpers,
 * zu dem sie gehören.
 */
typedef Color NodeStatus;

/**
 * Farbe eines Blatts, welches außerhalb aller Körper sich befindet und
 * somit zu keinem Körper gehört.
 */
const NodeStatus NO_OBJECT= 0;

/**
 * Farbe eines Blatts, für welches unbestimmt ist, ob bzw. zu welchem Körper 
 * es gehört.
 */
const NodeStatus UNDEF_OBJ= (-MAX_COLOR - 2);

/**
 * Oktalbaumstruktur.
 *
 * Unterste Schicht.
 * Stellt Low-Level-Operationen für die Oktalbaumsturktur zur Verfügung.
 */
class OctStruct {
 public:
  struct Node;
  /**
   * Oktalbaumstruktur-Typ.
   */
  typedef Node* _octree;

  /**
   * Löscht die Oktalbaumstruktur. Gibt den für den Oktalbaum eventuell
   * allozierten Speicher wieder frei und definiert den Wurzelknoten
   * als Blatt, welches zu keinem Körper gehört.
   */
  void clear();

  /**
   * Ist die Oktalbaumstruktur leer?
   * @return \em true,  falls nach einem flush() der Wurzelknoten ein Blatt
   *                    ist, welches zu keinem Körper gehört.\n
   *         \em false, ansonsten
   */
  bool empty();

  /**
   * Gewährleistet, dass die Oktalbaumstruktur minimiert ist.
   * Sugessive: Falls ein Knoten nur Blätter gleicher Farbe enthält,
   * werden die Blätter gelöscht. Der Knoten wird zum Blatt und übernimmt
   * die Farbe seiner Blätter.
   */
  void flush();

  /**
   * Liefert den höchsten Farbwert zurück, den die Oktalbaumblätter
   * enthalten.
   * @return \f{ \max_{ {\mbox{node}\ \in \ \mbox{OctStruct}\ |\ 
   *                        \mbox{isLeaf(node)} } }
   *                {\mbox{getColor(node)} }  \f}
   */
  Color getMaxColor();

  /**
   * Liefert die Größe eines Knotens im Speicher in Bytes
   * @return von einem Knoten belegter Speicher / Bytes
   */
  size_t getNodeSize();

  /**
   * Liefert die Oktalbaumstruktur.
   * @return Adresse des Wurzelknotens der Oktalbaumstruktur.
   */
  _octree& getTree();

  /**
   * Gibt den Oktalbaum auf der Konsole aus.
   */
  void print();

  /**
   * Liefert die Statistik über das Modell. 
   * @param h Baumhöhe
   * @param sumNodes Anzahl aller Oktalbaum-Knoten
   * @param leafs Anzahl der Blätter
   * @param borderNodes Anzahl der Randknoten der Geometrie
   * @param innerNodes Anzahl der inneren Knoten
   * @param normCells Anzahl der Normzellen der Geometrie (unterste Ebene)
   */
  void stat(Hight h, unsigned &sumNodes, unsigned &leafs, 
	    unsigned &innerNodes, unsigned &borderNodes, unsigned &normCells);

 protected:
  /**
   * Typ für Knoten im Oktalbaum
   */
  struct Node {
    /**
     * Unterpatitionierende Kinderknoten für innere Knoten des Oktalbaums,
     * NULL für Blätter.
     */
    struct Node *parts;

    /**
     * Knotenattribut.
     * - für Blätter:       Blattfarbe und NO_OBJECT falls das Blatt zu keinem
     *                      Körper gehört\n
     * - für innere Knoten: undefinert.
     */
    NodeStatus flag;
  };

  /**
   * Default-Konstruktor.
   * Erzeugt einen neuen leeren Oktalbaum.
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   */
  OctStruct() throw (NotEnoughMemoryException*);

  /**
   * Erzeugt ein neue Oktalbaumstruktur mit OCT_PARTS Blättern,
   * die zu keinem Körper gehören.
   * @return neue Oktalbaumstruktur
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   * @post \c return != NULL
   */
  _octree createLeafs() throw (NotEnoughMemoryException*);

  /**
   * Erzeugt ein Blattknoten, der zu keinem Körper gehören.
   * @return neuer Blattknoten
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              den neuen Blattknoten zu allozieren.
   * @post \c return != NULL
   */
  _octree createOneLeaf() throw (NotEnoughMemoryException*);

  /**
   * Gibt es tree?
   * @return tree != NULL
   */
  bool exist(_octree tree);

#ifdef MARK_BORDER
  /**
   * Liefert die 'richtige' Farbe eines Randknotens.
   * @param node Randknoten
   * @return Normfarbe des Knotens
   * @pre isBorderNode(node)
   */
  Color getBorderColor(Node node);
#endif

  /**
   * Liefert den Zeiger auf die i-te direkte Unterpartition.
   * @param parent Baum-Vaterknoten
   * @param i Nr. der Unterpartition
   * @return Zeiger auf den i-ten Kindsknoten
   * @pre exist(parent)
   * @pre !isLeaf(*parent)
   */
  _octree getChild(_octree parent, PartType i);

  /**
   * Liefert die Farbe eines Blattknotens.
   * @param node Blattknoten
   * @return Farbe des Blattknotens
   * @pre isLeaf(node)
   */
  Color getColor(Node node);

#ifdef MARK_BORDER
  /**
   * Ist der Knoten mit einer Randfarbe markiert?
   * @param node Blattknoten
   * @return Ob node mit einer Randfarbe markiert ist.
   * @pre isLeaf(node)
   */
  bool isBorderNode(Node node);
#endif

  /**
   * Ist der Knoten node ein Blatt?
   * @return true,  falls node ein Blatt ist.\n
   *         false, falls node ein innerer Knoten ist.
   */
  bool isLeaf(Node node);

  /**
   * Gehört der Knoten zu keinem Körper?
   * @pre isLeaf(node)
   * return getColor(node) == NO_OBJECT
   */
  bool isNoObject(Node node);

  /**
   * Ist undefiniert, ob der Knoten zu einem / zu welchem Körper gehört?
   * @pre isLeaf(node)
   * return getColor(node) == UNDEF_OBJ
   */
  bool isUndefObj(Node node);

  /**
   * Löscht die Teil-Oktalbaumstruktur und gibt den Speicher wieder frei.
   * Tut nichts, falls subtree == NULL.
   * @param subtree Teil-Oktalbaumstruktur
   */
  void remove(_octree &subtree);

#ifdef MARK_BORDER
  /**
   * Setzt node als Randknoten mit der Normfarbe color
   * @param node Blattknoten
   * @param color Normfarbe
   * @pre isLeaf(node)
   * @pre color >= NO_OBJECT
   */
  void setBorderColor(Node &node, Color color);
#endif

  /**
   * Setzt die Farbe des Blatts.
   * @param node Blattknoten
   * @param color Blattfarbe
   * @pre isLeaf(node);
   * @pre color >= NO_OBJECT
   */
  void setColor(Node &node, Color color);

  /**
   * Ersetzt die Oktalbaumstruktur durch tree.
   * Zum Freigeben des Speichers, der durch die alte Oktalbaumstruktur
   * belegt ist, muss explizit clear() aufgerufen werden.
   * @param tree neue Oktalbaumstruktur
   * @exception NotEnoughMemoryException Nicht genügend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   */
  void setTree(_octree &tree) throw (NotEnoughMemoryException*);

  /**
   * Anzahl der eingef"ugten Randknoten
   */
  unsigned countBorderNodes;

 private:
  /**
   * Überprüft, ob sich die direkten Unterpartitionen zusammenfassen lassen.
   * In die Überprüfung werden nur die direkten Kinderknoten einbezogen.
   * @param node Knoten
   * @param color Farbe aller Unterpartitionen, wenn alle die gleiche Farbe 
   *          haben. Undefiniert, falls sich die direkten Unterpartitionen 
   *          nicht zusammenfassen lassen.
   */
  bool canCompact(Node node, Color &color);

  /**
   * Minimiert den gesamten Baum, der sich unter node befindet, indem
   * Unterpartitionen mit gleicher Farbe zusammengefasst werden.
   * @param node Knoten
   */
  void compact(Node &node);

  /**
   * Kompaktisiert den Knoten node zu einem Blatt der Farbe color.
   * @param node Knoten
   * @param color Farbe
   */
  void compact(Node &node, Color color);

  /**
   * Gibt den Oktalbaum, der sich node befindet (incl. node) auf dem
   * Bildschirm aus.
   * @param node Knoten
   */
  void printTree(Node node);

  /**
   * Definiert node als Blattknoten.
   * @param node Knoten 
   * \note Für Unterpartitionen eventuell allozierter Speicher wird
   * nictht wieder freigegeben.
   */
  void setLeaf(Node &node);

  /**
   * Traversiert über den Oktalbaum, um die Statistik für das Modell
   * zu ermitteln. 
   * @param tree Oktal(teil)baum
   * @param h (Teil)Baumhöhe
   * @param sumNodes Anzahl aller Oktalbaum-Knoten
   * @param leafs Anzahl der Blätter
   * @param innerNodes Anzahl der inneren Knoten
   * @param normCells Anzahl der Normzellen der Geometrie (unterste Ebene)
   */
  void stat(_octree tree, Hight h, unsigned &sumNodes, unsigned &leafs, 
	    unsigned &innerNodes, unsigned &normCells);

  /**
   * Adresse des Wurzelknotens der Oktalbaumstruktur.
   * @invariant root != NULL
   */
  _octree root;
};

#endif // ! __OCT_STRUCT_H__

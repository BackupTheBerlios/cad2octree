/**
 * @file src/octree/fill_oct.h
 * 'F�llbarer' Oktalbaum.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __FILL_OCT_H__
#define __FILL_OCT_H__

#include <global.h>

#if !defined(CLASSIC_MODE) && defined(FILL_SOLIDS)

#include <octree/index_oct.h>
#include <generator/oct_gen.h>
#include <octree/idx_holder.h>

/**
 * 'F�llbarer' Oktalbaum.
 *
 * Stellt Operationen f�r das F�llen des Oktalbaums zur Verf�gung.
 */
class FillOct : public IndexOct {
 public:
  /**
   * Konstrukor.
   * @param idxOct 'indizierter' Oktalbaum
   */
  FillOct(IndexOct idxOct);

  /**
   * F�llt die K�rper innerhalb des Oktalbaums mit ihrer Farbe
   * und Knoten au�erhalb eines K�rpers mit NO_OBJECT.
   * Das hei�t es werden alle undefinierten Knoten (isUndefObj(node))
   * auf ihre richtige Farbe gesetzt.
   * Der Generator wird f�r die Lokalisation der Knoten (befindet sich
   * der Knoten in einem K�rper?) ben�tigt.
   * @param generator Oktalbaumgenerator
   * @pre generator != NULL
   */
  void fill(OctGen* generator);

 private: 
  /**
   * Falls idx UNDEF_OBJ ist, wird seine Farbe auf fillColor gesetzt und 
   * idx zu fillPoints getan. 
   * @param idx Knoten-Index
   */
  void add(NodeIndex idx);

  /**
   * Ausgehend von den Punkten in fillPoints wird das umliegende Gebiet 
   * mit fillColor gef�llt.
   */
  void fill();
 
  /**
   * F�llt den Teil des �bergebenen subtree mit color, der
   * auf der Achse axis auf der Seite partOfs liegt.
   * Falls es sich um ein Blattknoten handelt, wird dieser gef�llt.
   * Dabei bedeutet F�llen, dass f�r Knoten mit isUndefObj() die
   * Farbe auf color gesetzt wird. F�r solche Knoten werden auch die
   * Nachbarn gef�llt, indem sie in fillPoints gelegt werden.
   * @param subtree Zeiger auf den Oktalbaumknoten myIdx
   * @param myIdx Index des Knotens
   * @param axis genutzte Achse, um zu diesem Knoten als Nachbar zu gelangen
   *             (wird f�r die Unterbaumbetrachtung ben�tigt)
   * @param partOfs 0, falls 'vorderer' und 1 falls 'hinterer' Teil des
   *             subtree gef�llt werden soll
   */
  void fillParts(_octree subtree, NodeIndex myIdx, Axis axis, AxIndex partOfs);

  /**
   * F�llt den Teil des �bergebenen myIdx mit color, der
   * auf der Achse axis auf der Seite partOfs liegt.
   * Falls es sich um ein Blattknoten handelt, wird dieser gef�llt.
   * Dabei bedeutet F�llen, dass f�r Knoten mit isUndefObj() die
   * Farbe auf color gesetzt wird. F�r solche Knoten werden auch die
   * Nachbarn gef�llt, indem sie in fillPoints gelegt werden.
   * @param myIdx Index des Knotens
   * @param axis genutzte Achse, um zu diesem Knoten als Nachbar zu gelangen
   *             (wird f�r die Unterbaumbetrachtung ben�tigt)
   * @param partOfs 0, falls 'vorderer' und 1 falls 'hinterer' Teil des
   *             subtree gef�llt werden soll
   */
  void fillParts(NodeIndex myIdx, Axis axis, AxIndex partOfs);

  /**
   * F�llt die K�rper innerhalb des Teilbaums subtree mit ihrer Farbe
   * und Knoten au�erhalb eines K�rpers mit NO_OBJECT.
   * Das hei�t es werden alle undefinierten Knoten (isUndefObj(node))
   * auf ihre richtige Farbe gesetzt.
   * Der Generator wird f�r die Lokalisation der Knoten (befindet sich
   * der Knoten in einem K�rper?) ben�tigt.
   * @param subtree Teilbaum
   * @param myIdx Index des Vaterknotens des Teilbaums
   * @param generator Oktalbaumgenerator
   * @pre generator != NULL
   */
  void fillTree(_octree subtree, NodeIndex myIdx, OctGen* generator);

#ifdef SAVED_FILL
  /**
   * Liefert die Farbe eines Punktes, die als F�llfarbe genutzt werden soll.
   * @param savedfill (out) Ist die F�llfarbe sicher? (Die Farbe, die f�r die 
   * 		      Nachbarpunkte bestimmt wurde, ist die gleiche oder kann 
   *                  entsprechend der Nachbar-Farbe im Oktalbaum als sicher 
   *                  angesehen werden. 
   * @return F�llfarbe 
   */
  Color getColor(OctGen* generator, NodeIndex p, bool &savedFill);
#endif

  /**
   * F�llfarbe.
   */
  Color fillColor;

  /**
   * Speicher f�r F�llpunkte.
   */
  IdxHolder fillPoints;

#ifdef LIMITED_STACK
  /**
   * Weiterf�llen versuchen, da das F�llen wegen Erreichen der maximalen 
   * Itemzahl in fillPoints abgebrochen wurde? 
   */
  bool fillFurther;
  
  /**
   * F�llpunkt f�r das Wiederaufsetzen des F�llverfahrens bei 
   * fillFurther= true.
   */
  NodeIndex keptPoint;
#endif // LIMITED_STACK

};

#endif // !CLASSIC_MODE && FILL_SOLIDS

#endif // ! __FILL_OCT_H__

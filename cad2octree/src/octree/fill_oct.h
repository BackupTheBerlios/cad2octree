/**
 * @file src/octree/fill_oct.h
 * 'Füllbarer' Oktalbaum.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
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
 * 'Füllbarer' Oktalbaum.
 *
 * Stellt Operationen für das Füllen des Oktalbaums zur Verfügung.
 */
class FillOct : public IndexOct {
 public:
  /**
   * Konstrukor.
   * @param idxOct 'indizierter' Oktalbaum
   */
  FillOct(IndexOct idxOct);

  /**
   * Füllt die Körper innerhalb des Oktalbaums mit ihrer Farbe
   * und Knoten außerhalb eines Körpers mit NO_OBJECT.
   * Das heißt es werden alle undefinierten Knoten (isUndefObj(node))
   * auf ihre richtige Farbe gesetzt.
   * Der Generator wird für die Lokalisation der Knoten (befindet sich
   * der Knoten in einem Körper?) benötigt.
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
   * mit fillColor gefüllt.
   */
  void fill();
 
  /**
   * Füllt den Teil des übergebenen subtree mit color, der
   * auf der Achse axis auf der Seite partOfs liegt.
   * Falls es sich um ein Blattknoten handelt, wird dieser gefüllt.
   * Dabei bedeutet Füllen, dass für Knoten mit isUndefObj() die
   * Farbe auf color gesetzt wird. Für solche Knoten werden auch die
   * Nachbarn gefüllt, indem sie in fillPoints gelegt werden.
   * @param subtree Zeiger auf den Oktalbaumknoten myIdx
   * @param myIdx Index des Knotens
   * @param axis genutzte Achse, um zu diesem Knoten als Nachbar zu gelangen
   *             (wird für die Unterbaumbetrachtung benötigt)
   * @param partOfs 0, falls 'vorderer' und 1 falls 'hinterer' Teil des
   *             subtree gefüllt werden soll
   */
  void fillParts(_octree subtree, NodeIndex myIdx, Axis axis, AxIndex partOfs);

  /**
   * Füllt den Teil des übergebenen myIdx mit color, der
   * auf der Achse axis auf der Seite partOfs liegt.
   * Falls es sich um ein Blattknoten handelt, wird dieser gefüllt.
   * Dabei bedeutet Füllen, dass für Knoten mit isUndefObj() die
   * Farbe auf color gesetzt wird. Für solche Knoten werden auch die
   * Nachbarn gefüllt, indem sie in fillPoints gelegt werden.
   * @param myIdx Index des Knotens
   * @param axis genutzte Achse, um zu diesem Knoten als Nachbar zu gelangen
   *             (wird für die Unterbaumbetrachtung benötigt)
   * @param partOfs 0, falls 'vorderer' und 1 falls 'hinterer' Teil des
   *             subtree gefüllt werden soll
   */
  void fillParts(NodeIndex myIdx, Axis axis, AxIndex partOfs);

  /**
   * Füllt die Körper innerhalb des Teilbaums subtree mit ihrer Farbe
   * und Knoten außerhalb eines Körpers mit NO_OBJECT.
   * Das heißt es werden alle undefinierten Knoten (isUndefObj(node))
   * auf ihre richtige Farbe gesetzt.
   * Der Generator wird für die Lokalisation der Knoten (befindet sich
   * der Knoten in einem Körper?) benötigt.
   * @param subtree Teilbaum
   * @param myIdx Index des Vaterknotens des Teilbaums
   * @param generator Oktalbaumgenerator
   * @pre generator != NULL
   */
  void fillTree(_octree subtree, NodeIndex myIdx, OctGen* generator);

#ifdef SAVED_FILL
  /**
   * Liefert die Farbe eines Punktes, die als Füllfarbe genutzt werden soll.
   * @param savedfill (out) Ist die Füllfarbe sicher? (Die Farbe, die für die 
   * 		      Nachbarpunkte bestimmt wurde, ist die gleiche oder kann 
   *                  entsprechend der Nachbar-Farbe im Oktalbaum als sicher 
   *                  angesehen werden. 
   * @return Füllfarbe 
   */
  Color getColor(OctGen* generator, NodeIndex p, bool &savedFill);
#endif

  /**
   * Füllfarbe.
   */
  Color fillColor;

  /**
   * Speicher für Füllpunkte.
   */
  IdxHolder fillPoints;

#ifdef LIMITED_STACK
  /**
   * Weiterfüllen versuchen, da das Füllen wegen Erreichen der maximalen 
   * Itemzahl in fillPoints abgebrochen wurde? 
   */
  bool fillFurther;
  
  /**
   * Füllpunkt für das Wiederaufsetzen des Füllverfahrens bei 
   * fillFurther= true.
   */
  NodeIndex keptPoint;
#endif // LIMITED_STACK

};

#endif // !CLASSIC_MODE && FILL_SOLIDS

#endif // ! __FILL_OCT_H__

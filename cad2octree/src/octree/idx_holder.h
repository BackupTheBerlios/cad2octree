/**
 * @file src/octree/idx_holder.h
 * Zwischenspeicher für NodeIndex.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __IDX_HOLDER_H__
#define __IDX_HOLDER_H__

#include <global.h>

#if !defined(CLASSIC_MODE) && defined(FILL_SOLIDS)

#include <node_index.h>

#if defined(LIMITED_STACK) || defined(MARK_BORDER) 

#ifdef USE_QUEUE 

#include <utils/data_queue.h>

#else // !USE_QUEUE

#include <utils/data_stack.h>

#endif // !USE_QUEUE

#else // !LIMITED_STACK && !MARK_BORDER

#include <utils/data_holder.h>

#ifdef USE_QUEUE

#include <queue>

#else // !USE_QUEUE

#include <stack>

#endif // !USE_QUEUE

#endif // !LIMITED_STACK && !MARK_BORDER

/**
 * Zwischenspeicher für NodeIndex.
 *
 * Stack bzw. Queue für NodeIndex. Wird von FillOct verwendet. 
 * Queue, falls Optionsschalter USE_QUEUE gesetzt ist, ansonsten Stack. 
 * Sind die Optionsschalter LIMITED_STACK oder MARK_BORDER gesetzt, ist 
 * der IdxHolder auf MAX_RECURSIVE_DEEP begrenzt. Ist MAX_RECURSIVE_DEEP <= 0, 
 * wird die maximale Größe des IdxHolder adaptiv aus der maximalen Baumhöhe 
 * treeHight bestimmt. Ansonsten bleibt dieser Parameter unberücksichtigt. 
 */
#if defined(MARK_BORDER) || defined(LIMITED_STACK)

#if MAX_RECURSIVE_DEEP <= 0 

/**
 * Anzahl der Elemente, die maximal im DataHolder (DataStack bzw. DataQueue)
 * gepseichert werden können.
 */
#define HOLDER_SIZE (DIMENSIONS << treeHight)

#else // MAX_RECURSIVE_DEEP > 0

/**
 * Anzahl der Elemente, die maximal im DataHolder (DataStack bzw. DataQueue)
 * gepseichert werden können.
 */
#define HOLDER_SIZE MAX_RECURSIVE_DEEP

#endif // MAX_RECURSIVE_DEEP > 0

#ifdef USE_QUEUE

class IdxHolder : public DataQueue<NodeIndex> {

#else // !USE_QUEUE

class IdxHolder : public DataStack<NodeIndex> {

#endif // !USE_QUEUE

#else // !MARK_BORDER && !LIMITED_STACK

class IdxHolder {

#endif // !MARK_BORDER && !LIMITED_STACK

 public:
  /**
   * Konstrukor.
   * @param treeHight maximale Baumtiefe 
   */
  inline IdxHolder(Hight treeHight) 
#if defined(LIMITED_STACK) || defined(MARK_BORDER)

#ifdef USE_QUEUE

    : DataQueue<NodeIndex>(HOLDER_SIZE) {

#else // !USE_QUEUE

    : DataStack<NodeIndex>(HOLDER_SIZE) {

#endif // !USE_QUEUE

#else // !LIMITED_STACK && !MARK_BORDER
    {

#endif // !LIMITED_STACK && !MARK_BORDER

    }

  /**
   * Liefert das aktuelle Item und löscht es aus dem Datenspeicher.
   * @return aktuelles Element
   * @pre !isEmpty()
   */
  NodeIndex get();

  /**
   * Ist der Datenspeicher leer?
   * @return Ob der Datenspeicher kein Item enthält.
   */
  bool isEmpty(); 

  /**
   * Ist der Datenspeicher voll?
   * @return false 
   */
  bool isFull(); 

  /**
   * Legt das Element item auf dem Datenspeicher ab.
   * @param item Element
   */
  void put(NodeIndex item); 

#if !defined(MARK_BORDER) && !defined(LIMITED_STACK)
 private:
  /**
   * Datenspeicher. 
   */
#ifdef USE_QUEUE
  queue<NodeIndex> pool;
#else // !USE_QUEUE  
  stack<NodeIndex> pool;
#endif // !USE_QUEUE

#endif // !MARK_BORDER && !LIMITED_STACK

};

#endif // !CLASSIC_MODE && FILL_SOLIDS

#endif // ! __IDX_HOLDER_H__

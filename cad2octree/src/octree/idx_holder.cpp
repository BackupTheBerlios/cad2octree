/**
 * file: src/octree/idx_holder.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <octree/idx_holder.h>

#if !defined(CLASSIC_MODE) && defined(FILL_SOLIDS)

// ##### get() #######################################################
NodeIndex IdxHolder::get() {
#if defined(MARK_BORDER) || defined(LIMITED_STACK)

#ifdef USE_QUEUE
  return DataQueue<NodeIndex>::get();
#else // !USE_QUEUE
  return DataStack<NodeIndex>::get();
#endif // !USE_QUEUE

#else // !MARK_BORDER && !LIMETED_STACK

  assert (!isEmpty());

#ifdef USE_QUEUE
  NodeIndex retVal= pool.front();
#else // !USE_QUEUE
  NodeIndex retVal= pool.top();
#endif // !USE_QUEUE

  pool.pop();
  return retVal;

#endif // !MARK_BORDER && !LIMITED_STACK
}

// ##### isEmpty() ###################################################
bool IdxHolder::isEmpty() {
#if defined(MARK_BORDER) || defined(LIMITED_STACK)

#ifdef USE_QUEUE
  return DataQueue<NodeIndex>::isEmpty();
#else // !USE_QUEUE
  return DataStack<NodeIndex>::isEmpty();
#endif // !USE_QUEUE

#else // !MARK_BORDER && !LIMITED_STACK

  return pool.empty();

#endif // !MARK_BORDER && !LIMITED_STACK
}

// ##### isFull() ####################################################
bool IdxHolder::isFull() {
#if defined(MARK_BORDER) || defined(LIMITED_STACK)

#ifdef USE_QUEUE
  return DataQueue<NodeIndex>::isFull();
#else // !USE_QUEUE
  return DataStack<NodeIndex>::isFull();
#endif // !USE_QUEUE

#else // !MARK_BORDER && !LIMETED_STACK

  return false;

#endif // !MARK_BORDER && !LIMITED_STACK
}

// ##### put() #######################################################
void IdxHolder::put(NodeIndex item) {
#if defined(MARK_BORDER) || defined(LIMITED_STACK)

#ifdef USE_QUEUE
  DataQueue<NodeIndex>::put(item);
#else // !USE_QUEUE
  DataStack<NodeIndex>::put(item);
#endif // !USE_QUEUE

#else // !MARK_BORDER && !LIMETED_STACK

  pool.push(item);

#endif // !MARK_BORDER && !LIMITED_STACK
}

#endif // !CLASSIC_MODE && FILL_SOLIDS

// EOF: src/octree/idx_holder.cpp

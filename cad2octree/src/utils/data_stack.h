/**
 * @file src/utils/data_stack.h
 * Stack.
 *
 * Template f"ur einen Stapel. 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DATA_STACK_H__
#define __DATA_STACK_H__

#include <data_holder.h>

/**
 * Stack.
 *
 * Template f"ur einen Stapel. 
 */
template <class ItemType> class DataStack : protected DataHolder<ItemType> {
 public:
  /**
   * Konstruktor.
   * @param size Maximal-Größe [#Item] des zu erstellenden Daten-Stapels.
   */
  DataStack(unsigned long size) throw (NotEnoughMemoryException) 
      : DataHolder<ItemType>(size) {
  }

  /**
   * Liefert das aktuelle Item und löscht es aus dem Daten-Stapel.
   * @return aktuelles Element
   * @pre !isEmpty()
   */
  inline ItemType get() {
    assert (!isEmpty());
    
    --last;
    return pool[last];
  }
  
  /**
   * Ist der Daten-Stapel leer?
   * @return Ob der Daten-Stapel kein Item enthält.
   */
  inline bool isEmpty() {
    return last == 0;
  }

  /**
   * Ist der Datenspeicher voll?
   * @return Ob kein weiteres Element in den Datenspeicher aufgenommen werden 
   * 	     kann.
   */
  inline bool isFull() {
    return last == (getSize() - 1);
  }

};

#endif // ! __DATA_STACK_H__

/**
 * @file src/utils/data_queue.h
 * Queue.
 *
 * Template f"ur eine Schlange. 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DATA_QUEUE_H__
#define __DATA_QUEUE_H__

#include <data_holder.h>

/**
 * Queue.
 *
 * Template f"ur eine Schlange. 
 */
template <class ItemType> class DataQueue : protected DataHolder<ItemType> {
 public:
  /**
   * Konstruktor.
   * @param size Maximal-Größe [#Item] der zu erstellenden Daten-Schlange.
   */
  DataQueue(unsigned long size) throw (NotEnoughMemoryException) 
      : DataHolder<ItemType>(size), first(0) {
  }

  /**
   * Liefert das aktuelle Item und löscht es aus der Daten-Schlange.
   * @return aktuelles Element
   * @pre !isEmpty()
   */
  inline ItemType get() {
    assert (!isEmpty());
    
    ItemType retVal= pool[first];
    first= (first + 1) % getSize();
    return retVal;
  }
  
  /**
   * Ist die Daten-Schlange leer?
   * @return Ob die Daten-Schlange kein Item enthält.
   */
  inline bool isEmpty() {
    return first == last;
  }

  /**
   * Ist die Daten-Schlange voll?
   * @return Ob kein weiteres Element in die Daten-Schlange aufgenommen werden 
   * 	     kann.
   */
  inline bool isFull() {
    return ((last + 1) % getSize()) == first;
  }

 private:  
  /**
   * Erstes Element der Daten-Schlange.
   */
  unsigned long first;
 
};

#endif // ! __DATA_QUEUE_H__

/**
 * @file src/utils/data_holder.h
 * Virtueller Datenspeicher.
 *
 * Virtuelles Template f"ur einfache Container (Stack, Queue). 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __DATA_HOLDER_H__
#define __DATA_HOLDER_H__

#include <exception.h>

#include <assert.h>
#include <stdlib.h>

/**
 * Virtueller Datenspeicher.
 *
 * Virtuelles Template für einfache Container (Stack, Queue). 
 */
template <class ItemType> class DataHolder {
 public:
  /**
   * Konstruktor.
   * @param size Maximal-Größe [#Item] des zu erstellenden Datenspeichers.
   */
  DataHolder(unsigned long size) throw (NotEnoughMemoryException) 
      : last(0), size(size) {
    pool= (ItemType *)malloc(size * sizeof(ItemType));
    
    if (pool == NULL) {
      throw new NotEnoughMemoryException();
    }
  }

  /**
   * Destruktor.
   */
  virtual ~DataHolder() {
    free(pool);
  }

  /**
   * Liefert das aktuelle Item und löscht es aus dem Datenspeicher.
   * @return aktuelles Element
   * @pre !isEmpty()
   */
  virtual ItemType get()= 0;

  /**
   * Ist der Datenspeicher leer?
   * @return Ob der Datenspeicher kein Item enthält.
   */
  virtual bool isEmpty()= 0;

  /**
   * Ist der Datenspeicher voll?
   * @return Ob kein weiteres Element in den Datenspeicher aufgenommen werden 
   * 	     kann.
   */
  virtual bool isFull()= 0;

  /**
   * Legt das Element item auf dem Datenspeicher ab.
   * @param item Element
   * @pre !isFull()
   */
  inline void put(ItemType item) {
    assert (!isFull());
    
    pool[last]= item;
    last= (last + 1) % getSize();
  }

 protected:  
  /**
   * Liefert die Maximal-Größe des Datenspeichers [#Item].
   * @return Datenspeicher-Größe
   */
  inline unsigned long getSize() {
    return size;
  }
  
  /**
   * Letztes Element des Datenspeichers.
   */
  unsigned long last;
 
  /**
   * Item-Container.
   */
  ItemType* pool;

 private: 
  /**
   * Größe des Datenspeichers.
   */
  unsigned long size;

};

#endif // ! __DATA_HOLDER_H__

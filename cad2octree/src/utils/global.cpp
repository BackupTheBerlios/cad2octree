/**
 * file: src/utils/global.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <global.h>
#include <stdio.h>
#include <string.h>

typedef char* String;

// ##### ABS() #######################################################
Coordinate ABS(Coordinate x) {
  return (x >= 0 ? x : -x);
}

// ##### EQUIVAL() ###################################################
bool EQUIVAL(Coordinate coord1, Coordinate coord2) {
  return ABS((coord1) - (coord2)) < EPSILON;
}

// ##### SIGN() ######################################################
int SIGN(Coordinate x) {
  return EQUIVAL(x, 0.0) ? 0 : ( ((x) > 0.0) ? 1 : - 1 );
}

// ##### insSpace() ##################################################
void insSpace(String s, size_t i) {
  size_t l= strlen(s);
  char old= s[i];
  s[i]= ' ';
  char tmp= old;
  for (size_t x= i+1; x < l; ++x) {
    old= s[x];
    s[x]= tmp; 
    tmp= old;
  }
  s[l]= tmp;
  s[l+1]= '\0';
}

// ##### formatLarge() ###############################################
char* formatLarge(unsigned i) {
  char buf[100];
  sprintf(buf, "%d", i);
  size_t l= strlen(buf);
  
  for (size_t x= l%3; x < l; x+= 4, ++l) {
    insSpace(buf, x);
  }
  
  return strdup(buf);
}

// EOF: src/utils/global.cpp

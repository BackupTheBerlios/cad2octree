/**
 * file: src/utils/timer.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <timer.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

/**
 * Startzeit des Timer.
 */
#define START_TIME SEC_PER_DAY

// ##### Timer() #####################################################
Timer::Timer() {
  reset();
}

// ##### getTime() ###################################################
float Timer::getTime() {
  getitimer(ITIMER_REAL, &time);
  return (float)SEC_PER_DAY
    - (float)time.it_value.tv_sec
    - (float)time.it_value.tv_usec/(float)(USEC_PER_SEC);
}

// ##### getTime() ###################################################
const char* Timer::getTimeStr() {
  char buf[63]= "";

  getitimer(ITIMER_REAL, &time);

  long sec= SEC_PER_DAY - time.it_value.tv_sec;

  if (sec < 60) {
    // weniger als 1 Minute vergangen
    int oneHundreth= time.it_value.tv_usec/(USEC_PER_SEC/100);
    sprintf(buf, "%0ld.%s Sekunden", sec, toStr(oneHundreth, 100));
  } else if (sec < 3600) {
    // weniger als 1 Stunde vergangen
    sprintf(buf, "%0ld:%s Minuten", sec/60, toStr(sec, 60));
  } else {
    sprintf(buf, "%0ld:%s:%s h", sec/3600, toStr(sec/60, 60), toStr(sec, 60));
  }

  return strdup(buf);
}

// ##### print() #####################################################
void Timer::print() {
  printf("%s", getTimeStr());
  reset();
}

// ##### reset() #####################################################
void Timer::reset() {
  time.it_value.tv_sec = SEC_PER_DAY;
  time.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &time, 0);
}

// ##### toStr() #####################################################
char* Timer::toStr(long num, long maxNum) {
  num= num % maxNum;
  maxNum--;
  int dec= 0;
  for (; maxNum > 0; maxNum/= 10) {
    ++dec;
  }
  assert (dec <= 10);

  char str[10];
  for (int i= dec; i > 0; --i) {
    str[i-1]= char((num % 10) + '0');
    num/= 10;
  }
  str[dec]= '\0';

  return strdup(str);
}

// EOF: src/utils/timer.cpp

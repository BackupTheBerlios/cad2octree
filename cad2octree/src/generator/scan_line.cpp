/**
 * file: src/generator/scan_line.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <generator/scan_line.h>

#include <assert.h>

// ##### ScanLine() ##################################################
ScanLine::ScanLine(NodeIndex start, NodeIndex end) : current(start), 
    dir(NodeVec(start, end)), end(end), error(NULL_NODE_VEC) {
  assert (start.getHight() == end.getHight());
}

// ##### getCurrent() ################################################
NodeIndex ScanLine::getCurrent() {
  return current;
}

#ifndef COMB_SCAN_LINE
// ##### getError() ##################################################
AxIndex ScanLine::getError(Axis testAx) {
  NodeIndex testError= getErrorVec(testAx);

  return maxError(testError);
}
#endif

#ifdef COMB_SCAN_LINE
// ##### getErrorComb() ##############################################
AxIndex ScanLine::getErrorComb(AxComb testAxComb) {
  NodeIndex testError= getErrorCombVec(testAxComb);
  return maxError(testError);
}
#endif

#ifndef COMB_SCAN_LINE
// ##### getErrorVec() ###############################################
NodeIndex ScanLine::getErrorVec(Axis testAx) {
  NodeIndex retVal= error;
  AxIndex addErr= 1;

  for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
    if ((ax != testAx) && (dir[ax] != 0)) {
      addErr*= (dir[ax] < 0 ? -dir[ax] : dir[ax]);
    }
  }

  retVal.setCoordinate(testAx, retVal[testAx] + addErr);
  return retVal;
}
#endif

#ifdef COMB_SCAN_LINE
// ##### getErrorCombVec() ###########################################
NodeIndex ScanLine::getErrorCombVec(AxComb testAxComb) {
  NodeIndex retVal= error;
  AxIndex addErr= 1;

  for (Axis testAx= 0; testAx < DIMENSIONS; ++testAx) {
    if ((( (1 << testAx) & testAxComb ) != 0) && (dir[testAx] != 0)) {
      for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
	if ((ax != testAx) && (dir[ax] != 0)) {
	  addErr*= (dir[ax] < 0 ? -dir[ax] : dir[ax]);
	}
      }
      retVal.setCoordinate(testAx, retVal[testAx] + addErr);
    }
  }

  return retVal;
}
#endif

#ifndef COMB_SCAN_LINE
// ##### getNext() ###################################################
NodeIndex ScanLine::getNext(Axis ax) {
  assert (dir[ax] != 0);
  NodeIndex retVal= current;
  retVal.setCoordinate(ax, retVal[ax] + SIGN(dir[ax]));
  return retVal;
}
#endif

#ifdef COMB_SCAN_LINE
// ##### getNextComb() ###############################################
NodeIndex ScanLine::getNextComb(AxComb axComb) {
  assert (axComb > 0 && axComb <= (1 << DIMENSIONS));
  NodeIndex retVal= current;

  for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
    if (( (1 << ax) &  axComb ) != 0) {
      retVal.setCoordinate(ax, retVal[ax] + SIGN(dir[ax]));
    }
  }

  return retVal;
}
#endif

// ##### hasNext() ###################################################
bool ScanLine::hasNext() {
  return !(current == end);
}

// ##### maxError() ##################################################
AxIndex ScanLine::maxError(NodeIndex testError) {
  AxIndex max= testError[0];
  for (Axis ax= 1; ax < DIMENSIONS; ++ax) {
    if (max < testError[ax] && dir[ax] != 0) {
      max= testError[ax];
    }
  }
  return max;
}

// ##### minError() ##################################################
AxIndex ScanLine::minError(NodeIndex testError) {
  AxIndex min= testError[0];
  for (Axis ax= 1; ax < DIMENSIONS; ++ax) {
    if (min > testError[ax] && dir[ax] != 0) {
      min= testError[ax];
    }
  }
  return min;
}

// ##### next() ######################################################
void ScanLine::next() {
#ifndef COMB_SCAN_LINE
  Axis nextAx= 0;
  while ((dir[nextAx] == 0) && (nextAx < DIMENSIONS)) {
    ++nextAx;
  }
  assert (nextAx < DIMENSIONS);
  
  AxIndex minError= getError(nextAx);
  for (Axis ax= nextAx + 1; ax < DIMENSIONS; ++ax) {
    if (dir[ax] != 0) {
      AxIndex testErr= getError(ax);
      if (testErr < minError) {
        nextAx= ax;
	minError= testErr;
      }
    }
  }
  refreshError(nextAx);
  current= getNext(nextAx);
#else
  AxComb nextAxComb= 1;
  while ( (getNextComb(nextAxComb) == current) 
	  && (nextAxComb <= (1 << DIMENSIONS)) ) {
    ++nextAxComb;
  }
  assert (nextAxComb <= (1 << DIMENSIONS));
  
  AxIndex minError= getErrorComb(nextAxComb);
  for (AxComb axComb= nextAxComb + 1; axComb < (1 << DIMENSIONS); ++axComb) {
    if (!(getNextComb(axComb) == current)) {
      AxIndex testErr= getErrorComb(axComb);
      if (testErr < minError) {
        nextAxComb= axComb;
	minError= testErr;
      }
    }
  }
  refreshErrorComb(nextAxComb);
  current= getNextComb(nextAxComb);
#endif
}

#ifndef COMB_SCAN_LINE
// ##### refreshError() ##############################################
void ScanLine::refreshError(Axis stepAx) {
  error= getErrorVec(stepAx);
  AxIndex min= minError(error);
  for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
    if (dir[ax] != 0) {
      error.setCoordinate(ax, error[ax] - min);
    }
  }
}
#endif

#ifdef COMB_SCAN_LINE
// ##### refreshErrorComb() ##########################################
void ScanLine::refreshErrorComb(AxComb stepAxComb) {
  error= getErrorCombVec(stepAxComb);
  AxIndex min= minError(error);
  for (Axis ax= 0; ax < DIMENSIONS; ++ax) {
    if (dir[ax] != 0) {
      error.setCoordinate(ax, error[ax] - min);
    }
  }
}
#endif

// EOF: src/generator/scan_line.cpp

/**
 * file: src/cad/objects/b_spline.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <b_spline.h>

#include <assert.h>
#include <iostream>

// ##### BSpline() ###################################################
BSpline::BSpline(int m_count, bool pMeshClosedM, 
		 int n_count, bool pMeshClosedN)
  : closedM(pMeshClosedM), closedN(pMeshClosedN),
    countM(m_count), countN(n_count) {
}

// ##### ~BSpline() ##################################################
BSpline::~BSpline() {
  controlPoints.clear();
}

// ##### addCP() #####################################################
void BSpline::addCP(Point p) {
  controlPoints.insert(controlPoints.end(), p);
}

// ##### getCount() ##################################################
int BSpline::getCount(EXTENT axis) {
  assert (axis == M_DIR || axis == N_DIR);
  assert (controlPoints.size() == (unsigned)countN * countM);

  return (axis == M_DIR ? countM : countN);
}

// ##### getControlPoint() ###########################################
Point BSpline::getControlPoint(int m_idx, int n_idx) {
  if (m_idx >= getCount(M_DIR) && isClosed(M_DIR)) {
    m_idx-= getCount(M_DIR);
  }
  if (n_idx >= getCount(N_DIR) && isClosed(N_DIR)) {
    n_idx-= getCount(N_DIR);
  }

  assert (m_idx >= 0 && n_idx >= 0);
  assert (m_idx < getCount(M_DIR) && n_idx < getCount(N_DIR));

  return controlPoints[ ( m_idx % getCount(M_DIR) ) * getCount(N_DIR)
			+ (n_idx % getCount(N_DIR)) ];
}

// ##### getDataType() ###############################################
const CadObject::DataType BSpline::getDataType() {
  return CadObject::B_SPLINE;
}

// ##### getKnot() ###################################################
int BSpline::getKnot(EXTENT axis, int n_idx) {
  assert (axis == M_DIR || axis == N_DIR);
  assert (n_idx >= 0);
  assert (n_idx < getKnotCount(axis));

  if (isClosed(axis)) {
    return n_idx;
  }

  if (n_idx <= DEGREE) {
    return getKnotMin(axis);
  }
  if (n_idx > getCount(axis)) {
    return getKnotMax(axis);
  }

  return n_idx - DEGREE;
}

// ##### getKnotCount() ##############################################
int BSpline::getKnotCount(EXTENT axis) {
  assert (axis == M_DIR || axis == N_DIR);
  return (isClosed(axis) ? getCount(axis) + 2*DEGREE + 1
                         : getCount(axis) + DEGREE);
}

// ##### getKnotMax() ################################################
int BSpline::getKnotMax(EXTENT axis) {
  assert (axis == M_DIR || axis == N_DIR);
  return (isClosed(axis) ? getCount(axis) + DEGREE
                         : getCount(axis) - DEGREE);
}

// ##### getKnotMin() ################################################
int BSpline::getKnotMin(EXTENT axis) {
  assert (axis == M_DIR || axis == N_DIR);
  return (isClosed(axis) ? DEGREE : 0);
}

// ##### getMaxPoint() ###############################################
Point BSpline::getMaxPoint() {
  assert (!controlPoints.empty());

  Point maxPoint= getControlPoint(0, 0);
  for (int m= 0; m < getCount(M_DIR); ++m) {
    for (int n= 0; n < getCount(N_DIR); ++n) {
      maxPoint= maxPoint.max(getControlPoint(m, n));
    }
  }
  return maxPoint;
}

// ##### getMinPoint() ###############################################
Point BSpline::getMinPoint() {
  assert (!controlPoints.empty());

  Point minPoint= getControlPoint(0, 0);
  for (int m= 0; m < getCount(M_DIR); ++m) {
    for (int n= 0; n < getCount(N_DIR); ++n) {
      minPoint= minPoint.min(getControlPoint(m, n));
    }
  }
  return minPoint;
}

// ##### isClosed() ##################################################
bool BSpline::isClosed(EXTENT axis) {
  return (axis == M_DIR ? closedM : closedN);
}

// ##### print() #####################################################
void BSpline::print() {
  cout << "Spline : " << endl;
  cout << "\tM-Richtung: " << (closedM ? "closed " : "") << "[";
  for (int i= 0; i < getCount(M_DIR); ++i) {
    getControlPoint(i, 0).print();
  }
  cout << "]" << endl;
  cout << "\tN-Richtung: " << (closedN ? "closed " : "") << "[";
  for (int i= 0; i < getCount(N_DIR); ++i) {
    getControlPoint(0, i).print();
  }
  cout << "]" << endl << endl;
}

// EOF: src/cad/objects/spline.cpp

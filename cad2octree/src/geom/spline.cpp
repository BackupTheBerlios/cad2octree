/**
 * file: src/geom/spline.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <spline.h>

#include <assert.h>
#include <math.h>
#include <iostream>

#define M_DIR BSpline::M_DIR
#define N_DIR BSpline::N_DIR

// ##### Spline() ####################################################
Spline::Spline(BSpline bSpline, OctGen* generator)
  : gen(generator), h(BASE_NODE_HIGHT), spl(bSpline) {
}

// ##### ~Spline() ###################################################
Spline::~Spline() {
}

// ##### addToOctree() ###############################################
void Spline::addToOctree(Color color) {
  AxIndex k_max= getGranulty(M_DIR);
  AxIndex j_max= getGranulty(N_DIR);

  Coordinate k_low= Coordinate(spl.getKnotMin(M_DIR));
  Coordinate j_low= Coordinate(spl.getKnotMin(N_DIR));
  Coordinate k_step= Coordinate(spl.getKnotMax(M_DIR) - k_low)
                     / (Coordinate)k_max;
  Coordinate j_step= Coordinate(spl.getKnotMax(N_DIR) - j_low)
                     / (Coordinate)j_max;
  Coordinate k_old= k_low;
  Coordinate j_old= j_low;

  for (int k= 1; k <= k_max; ++k) {
    Coordinate k_high= k_low + k*k_step;
    for (int j= 1; j <= j_max; ++j) {
      Coordinate j_high= j_low + j*j_step;
      NodeIndex p[4] = {getFaceIndex(k_old, j_old),
			getFaceIndex(k_high, j_old),
			getFaceIndex(k_old, j_high),
			getFaceIndex(k_high, j_high)};
      gen->addQuadrilateral(p[0], p[1], p[3], p[2], color);
      j_old= j_high;
    }
    k_old= k_high;
  }
}

// ##### basisFuns() #################################################
void Spline::basisFuns(EXTENT axis, int i, Coordinate u, Coordinate N[]) {
  /* Quelle: Les Piegl, Wayne Tiller: The NURBS Book, Springer 1997 */
  assert (spl.getKnot(axis, i) <= u && u <= spl.getKnot(axis, i+1));
  Coordinate left[DEGREE+1];
  Coordinate right[DEGREE+1];

  N[0]= 1.0;
  for (int k= 1; k <= DEGREE; ++k) {
    N[k]= 0.0;
  }

  for (int j= 1; j <= DEGREE; j++) {
    left[j]= u - spl.getKnot(axis, i+1-j);
    right[j]= spl.getKnot(axis, i+j) - u;
    Coordinate saved= 0.0;
    Coordinate temp;
    for (int r= 0; r < j; r++) {
      assert (j - r <= DEGREE);
      assert (right[r+1]+left[j-r] != 0.0);

      temp= N[r]/(right[r+1]+left[j-r]);
      N[r]= saved + right[r+1]*temp;
      saved= left[j-r]*temp;
    }
    N[j]= saved;
  }

#ifndef NDEBUG
  Coordinate sum= 0.0;
  for (int j=0; j <= DEGREE; ++j) {
    sum+= N[j];
  }
  assert (EQUIVAL(sum, 1.0));
#endif
}

// ##### chkSplinePart() #############################################
bool Spline::chkSplinePart(GeomPoint p, 
			   GeomPoint & q, bool &intersect, bool &inside) {

#if defined(CLASSIC_MODE) || defined(ALGORITHM_ISIN) || !defined(CHK_CP_ONLY)

  intersect= false;
  inside= false;
  bool retVal= false;
  Coordinate dist= (RAY_DIR == FORWARD ? MAX_AX_INDEX : -MAX_AX_INDEX);
  Coordinate pCoord= p[RAY_AXIS];
  bool inter, in;

  AxIndex k_max= getGranulty(M_DIR);
  AxIndex j_max= getGranulty(N_DIR);

  Coordinate k_low= Coordinate(spl.getKnotMin(M_DIR));
  Coordinate j_low= Coordinate(spl.getKnotMin(N_DIR));
  Coordinate k_step= Coordinate(spl.getKnotMax(M_DIR) - k_low)
                     / (Coordinate)k_max;
  Coordinate j_step= Coordinate(spl.getKnotMax(N_DIR) - j_low)
                     / (Coordinate)j_max;
  Coordinate k_old= k_low;
  Coordinate j_old= j_low;

  for (int k= 1; k <= k_max; ++k) {
    Coordinate k_val= k_low + k*k_step;
    for (int j= 1; j <= j_max; ++j) {
      Coordinate j_val= j_low + j*j_step;
      GeomPoint idx[4] = {getFacePoint(k_old, j_old),
			  getFacePoint(k_val, j_old),
			  getFacePoint(k_old, j_val),
			  getFacePoint(k_val, j_val)};
      Polygon t[2]= {Polygon(idx[1], idx[3], idx[0]),
                     Polygon(idx[2], idx[0], idx[3])};
      for (int i= 0; i < 2; ++i) {
#ifdef CLASSIC_MODE
	t[i].setHight(getHight());
#endif
	assert (t[i].getHight() == getHight());
        if (t[i].testLine(p, q, inter, in)) {
	  Coordinate coord= q[RAY_AXIS];
	  if (inter) {
	    if ( (RAY_DIR == FORWARD) ? coord < dist && coord > pCoord
		                      : coord > dist && coord < pCoord ) {
	      dist= coord;
	      intersect= true;
	      inside= in;
	      retVal= true;
            }
	  }
	}
      }
      j_old= j_val;
    }
    k_old= k_val;
  }

  return retVal;

#else // !CLASSIC_MODE && !ALGORITHM_ISIN && !CHK_CP_ONY
  return true;
#endif // !CLASSIC_MODE && !ALGORITHM_ISIN && !CHK_CP_ONLY

}

// ##### findSpan() ##################################################
int Spline::findSpan(EXTENT axis, Coordinate u) {
  /* Quelle: Les Piegl, Wayne Tiller: The NURBS Book, Springer 1997 */
  int u_int= (int)u;

  if (spl.isClosed(axis)) {
    return u_int;
  }

  int n= spl.getCount(axis);
  if (u_int >= n) {
    return n;
  }

  return u_int + DEGREE;
}

// ##### getCP() #####################################################
GeomPoint Spline::getCP(int m_idx, int n_idx) {
  assert (gen != NULL);

  Point p= spl.getControlPoint(m_idx, n_idx);
  GeomPoint retVal= gen->getGenHelp()->getGeomPoint(p);
  assert (retVal.getHight() == BASE_NODE_HIGHT);
  return retVal;
}

// ##### getFaceIndex() ##############################################
NodeIndex Spline::getFaceIndex(Coordinate u, Coordinate v) {
  return getFacePoint(u, v).getNodeIndex();
}

// ##### getFacePoint() ##############################################
GeomPoint Spline::getFacePoint(Coordinate u, Coordinate v) {
  assert (spl.getKnotMin(M_DIR) <= u);
  assert (spl.getKnotMax(M_DIR) >= u);
  assert (spl.getKnotMin(N_DIR) <= v);
  assert (spl.getKnotMax(N_DIR) >= v);

  if ( !spl.isClosed(M_DIR) 
       && EQUIVAL(u, (Coordinate)spl.getKnotMax(M_DIR)) ) {
    u= (Coordinate)spl.getKnotMax(M_DIR) - EPSILON;
  }
  if ( !spl.isClosed(N_DIR) 
       && EQUIVAL(v, (Coordinate)spl.getKnotMax(N_DIR)) ) {
    v= (Coordinate)spl.getKnotMax(N_DIR) - EPSILON;
  }

  /* Quelle: Les Piegl, Wayne Tiller: The NURBS Book, Springer 1997 */
  Coordinate N_u[DEGREE+1];
  Coordinate N_v[DEGREE+1];

  int uSpan= findSpan(M_DIR, u);
  basisFuns(M_DIR, uSpan, u, N_u);
  int vSpan= findSpan(N_DIR, v);
  basisFuns(N_DIR, vSpan, v, N_v);

  GeomPoint s= GeomPoint(0.0, 0.0, 0.0);
  for (int i= 0; i <= DEGREE; ++i) {
    GeomPoint temp= GeomPoint(0.0, 0.0, 0.0);
    int v_ind= vSpan - DEGREE + i;
    for (int k= 0; k <= DEGREE; ++k) {
      int u_ind= uSpan - DEGREE + k;
      temp= temp + N_u[k]*getCP(u_ind, v_ind);
    }
    s= s + N_v[i]*temp;
  }
  return s;
}

// ##### getGranulty() ###############################################
AxIndex Spline::getGranulty(EXTENT axis) {
  assert (axis == M_DIR || axis == N_DIR);

  Coordinate idx[2][2]= {{spl.getKnotMin(M_DIR), spl.getKnotMax(M_DIR)},
                         {spl.getKnotMin(N_DIR), spl.getKnotMax(N_DIR)}};

  for (int i= 0; i < 2; ++i) {
    idx[i][1]= (idx[i][0] + idx[i][1]) / 2.0;
  }

  if (axis == M_DIR) {
    idx[1][0]= idx[1][1];
  } else {
    idx[0][0]= idx[0][1];
  }

  GeomPoint low= GeomPoint(getFacePoint(idx[0][0], idx[1][0]));
  GeomPoint high= GeomPoint(getFacePoint(idx[0][1], idx[1][1]));

  return (int)sqrt(2.0*GeomVec(low, high).getSqrLength()/VEC_ABS_MAX)+1;
}

// ##### getHight() ##################################################
Hight Spline::getHight() {
  return h;
}

// ##### isIn() ######################################################
bool Spline::isIn(GeomPoint p) {
  AxIndex k_max= getGranulty(M_DIR);
  AxIndex j_max= getGranulty(N_DIR);

  Coordinate k_low= Coordinate(spl.getKnotMin(M_DIR));
  Coordinate j_low= Coordinate(spl.getKnotMin(N_DIR));
  Coordinate k_step= Coordinate(spl.getKnotMax(M_DIR) - k_low)
                     / (Coordinate)k_max;
  Coordinate j_step= Coordinate(spl.getKnotMax(N_DIR) - j_low)
                     / (Coordinate)j_max;
  Coordinate k_old= k_low;
  Coordinate j_old= j_low;

  for (int k= 1; k <= k_max; ++k) {
    Coordinate k_high= k_low + k*k_step;
    for (int j= 1; j <= j_max; ++j) {
      Coordinate j_high= j_low + j*j_step;
      GeomPoint pP[4]= {getFacePoint(k_old, j_old),
			getFacePoint(k_high, j_old),
			getFacePoint(k_old, j_high),
			getFacePoint(k_high, j_high)};
      Polygon polygon[2]= {Polygon(pP[1], pP[3], pP[0]),
			   Polygon(pP[2], pP[0], pP[3])};
      for (int i= 0; i < 2; ++i) {
#ifdef CLASSIC_MODE
	polygon[i].setHight(getHight());
#endif
	if (polygon[i].isIn(p)) {
	  return true;
	}
      }
      j_old= j_high;
    }
    k_old= k_high;
  }
  return false;
}

// ##### print() #####################################################
void Spline::print() {
  cout << "Spline : " << endl;
  cout << "\tM-Richtung: " << (spl.isClosed(M_DIR) ? "closed " : "") << "[";
  for (int i= 0; i < spl.getCount(M_DIR); ++i) {
    getCP(i, 0).print();
  }
  cout << "]" << endl;
  cout << "\tN-Richtung: " << (spl.isClosed(N_DIR) ? "closed " : "") << "[";
  for (int i= 0; i < spl.getCount(N_DIR); ++i) {
    getCP(0, i).print();
  }
  cout << "]" << endl << endl;
}

// ##### setHight() ##################################################
void Spline::setHight(Hight hight) {
  h= hight;
}

// ##### testLine() ##################################################
bool Spline::testLine(GeomPoint p, GeomPoint &q,
		      bool &intersect, bool &inside) {
#ifndef CLASSIC_MODE
  p.setHight(BASE_NODE_HIGHT);
#endif
  assert (p.getHight() == getHight());
  intersect= false;
  inside= false;
  bool retVal= false;

#ifndef EXTRACT_PART
  Coordinate dist= (RAY_DIR == FORWARD ? MAX_AX_INDEX : -MAX_AX_INDEX);
  Coordinate pCoord= p[RAY_AXIS];
  bool inter, in;

  bool closed_m= spl.isClosed(M_DIR);
  bool closed_n= spl.isClosed(N_DIR);
  int m_max= spl.getCount(M_DIR) + closed_m - 1;
  int n_max= spl.getCount(N_DIR) + closed_n - 1;

  for (int v= 0; v < n_max && !intersect; ++v) {
    for (int u= 0; u < m_max && !intersect; ++u) {
      GeomPoint idx[4]= {getCP(u, v),   getCP(u+1, v), 
			 getCP(u, v+1), getCP(u+1, v+1)};
      Polygon t[2]= {Polygon(idx[1], idx[3], idx[0]),
		     Polygon(idx[2], idx[0], idx[3])};
      for (int i= 0; i < 2 && !intersect; ++i) {
#ifdef CLASSIC_MODE
	t[i].setHight(getHight());
#endif
	assert (t[i].getHight() == getHight());
	Coordinate coord= q[RAY_AXIS];
	if (t[i].testLine(p, q, inter, in)) {
	  if (inter
              && (RAY_DIR == FORWARD ? coord < dist && coord > pCoord
		                     : coord > dist && coord < pCoord) ) {
	    intersect= true;
	    inside= in;
	    retVal= true;
	  }
	} 
      }
    }
  }

  if (intersect) {
#else // EXTRACT_PART
  {
#endif // EXTRACT_PART
    return chkSplinePart(p, q, intersect, inside);
  }

  return retVal;
}

// EOF: src/geom/spline.cpp

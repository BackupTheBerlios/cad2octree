/**
 * file: src/generator/gen_help.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <generator/gen_help.h>

// ##### GenHelp() ###################################################
GenHelp::GenHelp(Hight maxTreeHight, Point minPoint, Point maxPoint)
  throw (NotEnoughMemoryException)
    : min(minPoint) {
  assert (!(minPoint == maxPoint));

  density= (Coordinate(1 << maxTreeHight) - (Coordinate)EPSILON)
           / getMaxExtent(minPoint, maxPoint);

  assert (!EQUIVAL(density, 0.0));
}

// ##### bestAxis() ##################################################
Axis GenHelp::bestAxis(NodeIndex current, NodeIndex end, NodeVec line,
		       Direction direction) {
  assert ( current.getHight() == end.getHight()
	   && end.getHight() == line.getHight() );

  Axis keptAxis= 0;
  NodeIndex testPoint= current;
  Coordinate minError= MAX_AX_INDEX*MAX_AX_INDEX*MAX_AX_INDEX;
  for (Axis axis= 0; axis < DIMENSIONS; ++axis) {
    if (direction[axis] != 0) {
      testPoint= current;
      testPoint.setCoordinate(axis, testPoint[axis] + direction[axis]);
      Coordinate error= getError(NodeVec(testPoint, end), line);
      if (error <= minError) {
	keptAxis= axis;
	minError= error;
      }
    }
  }
  return keptAxis;
}

// ##### getCadCoord() ###############################################
Coordinate GenHelp::getCadCoord(GeomPoint p, Axis axis) {
  assert (!EQUIVAL(density, 0.0));

  return min[axis] + p[axis] / density;
}

// ##### getCadPoint() ###############################################
Point GenHelp::getCadPoint(GeomPoint p) {
  assert (p.getHight() == BASE_NODE_HIGHT);

  Point retVal= Point(getCadCoord(p, X_AXIS),
		      getCadCoord(p, Y_AXIS),
		      getCadCoord(p, Z_AXIS));
  return retVal;
}

// ##### getError() ##################################################
Coordinate GenHelp::getError(NodeVec fromTestpoint, NodeVec line) {
  assert (fromTestpoint.getHight() == line.getHight());

  GeomVec geomLine= GeomPoint(line.getX(), line.getY(), line.getZ());
  GeomVec geomFromTp= GeomPoint(fromTestpoint.getX(), fromTestpoint.getY(),
				fromTestpoint.getZ());
  return geomFromTp.vec_prod(geomLine.getNormalize()).getSqrLength();
}

// ##### getGeomCoord() ##############################################
Coordinate GenHelp::getGeomCoord(Point p, Axis axis) {
  return density * (p[axis] - min[axis]);
}

// ##### getGeomPoint() ##############################################
GeomPoint GenHelp::getGeomPoint(Point p) {
  GeomPoint retVal= GeomPoint(getGeomCoord(p, X_AXIS),
			      getGeomCoord(p, Y_AXIS),
			      getGeomCoord(p, Z_AXIS),
			      BASE_NODE_HIGHT);
  return retVal;
}

// ##### getNodeIndex() ##############################################
NodeIndex GenHelp::getNodeIndex(Point p) {
  GeomPoint g= getGeomPoint(p);
  assert (g.getHight() == BASE_NODE_HIGHT);

  NodeIndex retVal= g.getNodeIndex();
  
  assert (retVal.getHight() == BASE_NODE_HIGHT);
  return retVal;
}

// ##### getMaxExtent() ##############################################
Coordinate GenHelp::getMaxExtent(Point min, Point max) {
  assert (min << max);
  
  Coordinate maxExtent= (max[0] - min[0]);
  for (Axis axis= 1; axis < DIMENSIONS; ++axis) {
    maxExtent= MAX(maxExtent, max[axis] - min[axis]);
  }
  return maxExtent;
}

// ##### getPolygon() ################################################
Polygon GenHelp::getPolygon(Quadrilateral *q, Polygon* &t2) {
  assert (q != NULL);
  t2= NULL;
  GeomPoint pA= getGeomPoint((*q)[0]);
  GeomPoint pB= getGeomPoint((*q)[1]);
  GeomPoint pC= getGeomPoint((*q)[2]);
  GeomPoint pD= getGeomPoint((*q)[3]);
  
  if (!Polygon(pA, pB, pC).isInPlane(pD)) {
    t2= new Polygon(pC, pD, pB);
    return Polygon(pA, pB, pD);
  }
  
  return Polygon(pA, pB, pC, pD);
}

// ##### getPolygon() 
Polygon GenHelp::getPolygon(Triangle *t) {
  assert (t != NULL);
  Polygon p= Polygon(getGeomPoint((*t)[0]), getGeomPoint((*t)[1]),
		     getGeomPoint((*t)[2]));
		     
  assert (p.getHight() == BASE_NODE_HIGHT);
  return p;
}

// EOF: src/generator/gen_help.cpp

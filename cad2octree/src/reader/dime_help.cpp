/**
 * file: src/reader/dime_help.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <reader/dime_help.h>

#include <cad/objects/b_spline.h>
#include <cad/objects/triangle.h>
#include <cad/objects/quadrilateral.h>

#include <octree/oct_struct.h>

// ##### DimeHelp() ##################################################
DimeHelp::DimeHelp(CadModel* cadModel, Color color, bool splitQuad) :
    cadModel(cadModel), color(color), 
    countCP(0), countQuad(0), countSplineFaces(0), countTriangles(0), 
    countVertices(0),
    splitQuadrilaterals(splitQuad) {
  assert (cadModel != NULL);
  assert (color > NO_OBJECT);
}

// ##### add() #######################################################
void DimeHelp::add(dimeEntity *entity) {
  assert (entity != NULL);

  switch (entity-> typeId()) {
  case dimeBase::dime3DFaceType:
    addPlane((dime3DFace *)entity);
    break;
  case dimeBase::dimePolylineType:
    addSpline((dimePolyline *)entity);
    break;
  }
}

// ##### addPlane() ##################################################
void DimeHelp::addPlane(dime3DFace* entity) {
  assert (cadModel != NULL);
  assert (entity != NULL);

  Point points[COUNT_VERTEX_IN_FACE]
    = {NULL_POINT, NULL_POINT, NULL_POINT, NULL_POINT};

  for (int i= 0; i < COUNT_VERTEX_IN_FACE; ++i) {
    points[i]= vertex2Point(entity->getVertex(i));
  }

  if (points[2] == points[3]) {
    cadModel->add(new Triangle(points[0], points[1], points[2]), color);
    countVertices+= 3;
    countTriangles++;
  } else {
    if (splitQuadrilaterals) {
      cadModel->add(new Triangle(points[1], points[3], points[0]), color);
      cadModel->add(new Triangle(points[1], points[2], points[3]), color);
      countTriangles+= 2;
      countVertices+= 6;
    } else {
      cadModel->add(new Quadrilateral(points[0], points[1], points[2], 
                                      points[3]), color);
      countQuad++;
      countVertices+= 4;
    }
  }
}

// ##### addSpline() #################################################
void DimeHelp::addSpline(dimePolyline* entity) {
  assert (cadModel != NULL);
  assert (entity != NULL);

  if (entity->getType() != dimePolyline::POLYGON_MESH) {
    return;
  }
  if (entity->getSurfaceType() != dimePolyline::CUBIC_BSPLINE) {
    cout << "Warning: POLYLINE is no cubic B-Spline!" << endl;
    entity->print();
    cout << endl;
    return;
  }

  int fl= entity->getFlags();

  assert (fl & dimePolyline::SPLINE_FIT);
  assert (fl & dimePolyline::IS_POLYMESH_3D);
  assert (entity->getElevation() == dimeVec3f(0, 0, 0));

  int countM= entity->getPolymeshCountM();
  int countN= entity->getPolymeshCountN();

  assert (entity->getPolymeshCountM() > 3);
  assert (entity->getPolymeshCountN() > 3);
  
  bool closedM= fl & dimePolyline::POLYMESH_CLOSED_M;
  bool closedN= fl & dimePolyline::POLYMESH_CLOSED_N;
  BSpline* spline= new BSpline(countM, closedM, countN, closedN);
  for (int i= 0; i < countM*countN; ++i) {
    dimeVertex* vertex= entity->getSplineFrameControlPoint(i);
    assert (vertex != NULL);
    Point p= vertex2Point(vertex->getCoords());
    spline->addCP(p);
    countCP++;
    countVertices++;
  }
  cadModel->add(spline, color);
  countSplineFaces++;
}

// ##### getModel() ##################################################
CadModel* DimeHelp::getCadModel() {
  assert (cadModel != NULL);

  cout << "#Spline-F.= " << countSplineFaces << endl;
  cout << "#Control-P.= " << countCP << endl;
  cout << "#Vertex= " << countVertices << endl;
  cout << "#Triangle= " << countTriangles << endl;
  cout << "#Quadrilat.= " << countQuad << endl;
  return cadModel;
}

// ##### vertex2Point() ##############################################
Point DimeHelp::vertex2Point(dimeVec3f v) {
  dxfdouble x, y, z;
  v.getValue(x, y, z);
  return Point((Coordinate)x, (Coordinate)y, (Coordinate)z);
}

// EOF src/reader/dime_help.cpp

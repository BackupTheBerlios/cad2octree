/**
 * file: src/octree/oct_gen.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <generator/oct_gen.h>

#include <generator/scan_line.h>
#include <octree/fill_oct.h>
#include <quadrilateral.h>
#include <triangle.h>
#include <spline.h>
#include <global.h>
#include <timer.h>

// ##### OctGen() ####################################################
OctGen::OctGen(CadModel* model) : cadModel(model) {
  assert (model != NULL);
}

// ##### add() #######################################################
void OctGen::add(NodeIndex p, Color color)
    throw (NotEnoughMemoryException*) {
  octree->add(p, color);
}

// ##### addLine() ###################################################
void OctGen::addLine(NodeIndex start, NodeIndex end, Color color)
    throw (NotEnoughMemoryException*) {
  assert (start.getHight() == end.getHight());
  assert (octree->isIn(start));
  assert (octree->isIn(end));

  ScanLine l= ScanLine(start, end);
  add(l.getCurrent(), color);
  while (l.hasNext()) {
    l.next();
    add(l.getCurrent(), color);
  }
}

// ##### addObject() #################################################
void OctGen::addObject(CadObject* object, Color color)
    throw (NotEnoughMemoryException*) {
  assert (object != NULL);
  switch (object->getDataType()) {
  case CadObject::POINT:
    octree->add(genHelp->getNodeIndex(*((Point *)object)), color);
    break;
  case CadObject::TRIANGLE:
#ifdef ALGORITHM_ISIN
    octree->add(new Polygon(genHelp->getPolygon((Triangle *)object)), color);
#else
    addTriangle( genHelp->getNodeIndex((*((Triangle *)object))[0]),
		 genHelp->getNodeIndex((*((Triangle *)object))[1]),
		 genHelp->getNodeIndex((*((Triangle *)object))[2]),
		 color);
#endif
    break;
  case CadObject::QUADRILATERAL:
#ifdef ALGORITHM_ISIN
      octree->add( new Polygon
	( genHelp->getPolygon(((Quadrilateral *)object)->getLowTriangle())),
	  color);
      octree->add( new Polygon
	( genHelp->getPolygon(((Quadrilateral *)object)->getHiTriangle())),
	  color);
#else
      addQuadrilateral( genHelp->getNodeIndex((*((Quadrilateral *)object))[0]),
		        genHelp->getNodeIndex((*((Quadrilateral *)object))[1]),
		        genHelp->getNodeIndex((*((Quadrilateral *)object))[2]),
		        genHelp->getNodeIndex((*((Quadrilateral *)object))[3]),
		        color);
#endif
    break;
  case CadObject::B_SPLINE:
    Spline* spline= new Spline(*(BSpline *)object, this);
#ifdef ALGORITHM_ISIN
    octree->add(spline, color);
#else
    spline->addToOctree(color);
#endif
    delete spline;
    break;
  }
}

// ##### addQuadrilateral() ##########################################
void OctGen::addQuadrilateral(NodeIndex pA, NodeIndex pB, NodeIndex pC,
			      NodeIndex pD, Color color)
    throw (NotEnoughMemoryException*) {
  assert (pA.getHight() == pB.getHight() && pB.getHight() == pC.getHight()
          && pC.getHight() == pD.getHight());
  assert (octree->isIn(pA));
  assert (octree->isIn(pB));
  assert (octree->isIn(pC));
  assert (octree->isIn(pD));

  ScanLine l1= ScanLine(pA, pB);
  ScanLine l2= ScanLine(pD, pC);
  addLine(l1.getCurrent(), l2.getCurrent(), color);
  while (l1.hasNext() || l2.hasNext()) {
    if (l1.hasNext()) {
      l1.next();
    }
    if (l2.hasNext()) {
      l2.next();
    }
    addLine(l1.getCurrent(), l2.getCurrent(), color);
  }
}

// ##### addTriangle() ###############################################
void OctGen::addTriangle(NodeIndex pA, NodeIndex pB, NodeIndex pC,
			  Color color)
    throw (NotEnoughMemoryException*) {
  assert (pA.getHight() == pB.getHight() && pB.getHight() == pC.getHight());
  assert (octree->isIn(pA));
  assert (octree->isIn(pB));
  assert (octree->isIn(pC));

  ScanLine l1= ScanLine(pA, pB);
  ScanLine l2= ScanLine(pA, pC);
  addLine(l1.getCurrent(), l2.getCurrent(), color);
  while (l1.hasNext() || l2.hasNext()) {
    if (l1.hasNext()) {
      l1.next();
    }
    if (l2.hasNext()) {
      l2.next();
    }
    addLine(l1.getCurrent(), l2.getCurrent(), color);
  }
}

// ##### checkModel() ################################################
void OctGen::checkModel() throw (WrongModelException*) {
  if (cadModel == NULL) {
    throw new WrongModelException();
  }
  if (cadModel->empty()) {
    throw new WrongModelException();
  }
  if (cadModel->getMinPoint() == cadModel->getMaxPoint()) {
    throw new WrongModelException();
  }
}

#ifdef CLASSIC_MODE
// ##### generateClassic() ###########################################
void OctGen::generateClassic(NodeIndex idx) {
  assert (cadModel != NULL);

  bool isAtBorder;
  Color color= testRayColor(idx, isAtBorder);
  
  if ((!isAtBorder) || (idx.getHight() == BASE_NODE_HIGHT)) {
    octree->add(idx, color);
    return;
  }
  
  for (PartType part= 0; part < OCT_PARTS; ++part) {
    generateClassic(octree->getChild(idx, part));
  }
}
#endif

// ##### getCadModel() ###############################################
CadModel* OctGen::getCadModel() {
  assert (cadModel != NULL);

  return cadModel;
}

#ifndef CLASSIC_MODE
// ##### getColor() ##################################################
Color OctGen::getColor(NodeIndex p) {
#ifdef RAY_METHODE
  return testRayColor(p);
#else
  return nextPointColor(p);
#endif
}
#endif

// ##### getGenHelp() ################################################
GenHelp* OctGen::getGenHelp() {
  assert (genHelp != NULL);

  return genHelp;
}

// ##### getGenTree() ################################################
IndexOct* OctGen::getGenTree() {
  assert (octree != NULL);

  return octree;
}

// ##### getOctree() #################################################
IndexOct* OctGen::getOctree(Hight maxTreeHight)
    throw (NotEnoughMemoryException*, WrongModelException*) {
  unsigned borderNodes, sumNodes, leafs, innerNodes, normcells;

  checkModel();
  Timer timer;
  octree= new IndexOct(maxTreeHight);
  genHelp= new GenHelp(maxTreeHight,
		       cadModel->getMinPoint(),
		       cadModel->getMaxPoint());

  cerr << "Extrahiere Spline-Flächen ..." << endl;
  timer.reset();
  
#ifdef CLASSIC_MODE
  cerr << "Erzeugen des Oktalbaums ..." << endl; 
  NodeIndex idx= NodeIndex(0, 0, 0, octree->getMaxTreeHight());
  generateClassic(idx);
  cout << endl;
  timer.print(); cout << " benötigt." << endl;  
#else // !CLASSIC_MODE
  cerr << "Einfügen der Oberflächen ..." << endl;
  unsigned maxCount= cadModel->count() - 1;
  cout << " [Nr] " <<  maxCount + 1 << endl;
  cadModel->first();
  while (cadModel->hasObject()) {
    Element obj= cadModel->getObject();
    assert (obj != NULL);
    addObject(obj, cadModel->getObjColor());
    cadModel->next();
  }
  timer.print(); cout << " benötigt." << endl;  

#ifdef FILL_SOLIDS
  octree->stat(octree->getMaxTreeHight(), 
	       sumNodes, leafs, innerNodes, borderNodes, normcells);
  cout << "#Knoten=" << formatLarge(sumNodes) 
       << ", #Blätter=" << formatLarge(leafs)
       << ", #innere Kn.=" << formatLarge(innerNodes) << endl;
  cout << "#Randknoten=" << formatLarge(borderNodes) 
       << ", #Normzellen=" << formatLarge(normcells) << endl;
  cout << "Filling...         " << endl;
  timer.reset();
  FillOct(*octree).fill(this);
  timer.print(); cout << " benötigt." << endl;
#endif // FILL_SOLIDS

#endif // !CLASSIC_MODE
  delete genHelp;
  octree->stat(octree->getMaxTreeHight(), 
	       sumNodes, leafs, innerNodes, borderNodes, normcells);
  cout << "#Knoten=" << formatLarge(sumNodes) 
       << ", #Blätter=" << formatLarge(leafs)
       << ", #innere Kn.=" << formatLarge(innerNodes) << endl;
  cout << "#Randknoten=" << formatLarge(borderNodes) 
       << ", #Normzellen=" << formatLarge(normcells) << endl;
  timer.reset();
  cout << "Flushing..." << endl;
  octree->flush();

  timer.print(); cout << " benötigt." << endl;
  octree->stat(octree->getMaxTreeHight(), 
	       sumNodes, leafs, innerNodes, borderNodes, normcells);
  cout << "#Knoten=" << formatLarge(sumNodes) 
       << ", #Blätter=" << formatLarge(leafs)
       << ", #innere Kn.=" << formatLarge(innerNodes) << endl;
  cout << "#Randknoten=" << formatLarge(borderNodes) 
       << ", #Normzellen=" << formatLarge(normcells) << endl;
  return octree;
}

// ##### nextPointColor() ############################################
Color OctGen::nextPointColor(NodeIndex p) {
  assert (p.getHight() == BASE_NODE_HIGHT);
  assert (cadModel != NULL);
  assert (octree != NULL);
  assert (genHelp != NULL);

  Color color;

  cadModel->first();
  while (!cadModel->getObject()->isPlane() && cadModel->hasObject()) {
    cadModel->next();
  }

  Coordinate sqrDist= MAX_AX_INDEX*MAX_AX_INDEX*MAX_AX_INDEX;
  GeomPoint footpoint= NULL_GEOM_VEC;
  Polygon polygon= Polygon(footpoint, footpoint, footpoint);
  color= NO_OBJECT;
  Polygon* t2= NULL;
  while (cadModel->hasObject()) {
    CadObject* object= cadModel->getObject();
    switch (object->getDataType()) {
    case CadObject::TRIANGLE:
      polygon= genHelp->getPolygon((Triangle *)object);
      break;
    case CadObject::QUADRILATERAL:
      polygon= genHelp->getPolygon((Quadrilateral *)object, t2);
      break;
    default:;
    }

    bool haveMorePolygons= true;
    while (haveMorePolygons) {
      footpoint= polygon.getFootpoint(p);
      if (!polygon.isIn(footpoint)) {
	return false;
      }
      GeomVec rayVec= GeomVec(GeomPoint(p), footpoint);
      Coordinate angle= polygon.getNormVec()*rayVec;
      if (EQUIVAL(rayVec.getSqrLength(), sqrDist)) {
      } else if (rayVec.getSqrLength() < sqrDist) {
	sqrDist= rayVec.getSqrLength();
	color= (angle <= 0.0) ? NO_OBJECT : cadModel->getObjColor();
      }
      
      if (t2 != NULL) {
	polygon= *t2;
	t2= NULL;
      } else {
	haveMorePolygons= false;
      }
    }
    
    cadModel->next();
  }
  return color;
}

// ##### testRayColor() ##############################################
#ifdef CLASSIC_MODE
Color OctGen::testRayColor(NodeIndex p, bool &isAtBorder) {
  isAtBorder= false;
#else
Color OctGen::testRayColor(NodeIndex p) {
#endif
  assert (cadModel != NULL);
  assert (octree != NULL);
  assert (genHelp != NULL);

  Axis rayAxis= RAY_AXIS;
  AxDirection rayDir= RAY_DIR;

  assert (rayAxis < DIMENSIONS);
  assert (rayDir == BACKWARD || rayDir == FORWARD);

  Color color= NO_OBJECT;
  bool intersect= false;
  bool inside= false;

  cadModel->first();
  GeomPoint idxPoint= GeomPoint(p);
  Coordinate dist= (rayDir == FORWARD ? MAX_AX_INDEX : -MAX_AX_INDEX);
  GeomPoint footpoint= NULL_GEOM_VEC;
  Surface *s= NULL;
  color= NO_OBJECT;
  Polygon *t2= NULL;
  while (cadModel->hasObject()) {
    CadObject* object= cadModel->getObject();
    switch (object->getDataType()) {
    case CadObject::TRIANGLE:
      s= new Polygon(genHelp->getPolygon((Triangle *)object));
      break;
    case CadObject::QUADRILATERAL:
      s= new Polygon(genHelp->getPolygon((Quadrilateral *)object, t2));
      break;
    case CadObject::B_SPLINE:
      s= new Spline(*(BSpline *)object, this);
      break;
    default:;
    }

#ifdef CLASSIC_MODE
    s->setHight(idxPoint.getHight());
#else
    idxPoint.setHight(BASE_NODE_HIGHT);
#endif
    assert (s->getHight() == idxPoint.getHight());

    Coordinate pCoord= idxPoint[rayAxis];
    bool haveMorePolygons= true;
    while (haveMorePolygons) {
      assert (s->getHight() == idxPoint.getHight());

#ifdef CLASSIC_MODE
      if (s->isIn(idxPoint)) {
        delete s;
	isAtBorder= true;
	inside= true;
	return cadModel->getObjColor();
      }
#endif
      if (s->testLine(idxPoint, footpoint, intersect, inside)) {
        Coordinate coord= footpoint[rayAxis];
	if (intersect) {
	  if ( (rayDir == FORWARD) ? coord < dist && coord > pCoord
	                           : coord > dist && coord < pCoord ) {
	    dist= coord;
	    color= (inside ? cadModel->getObjColor() : NO_OBJECT);
	  }
	}
      }
      delete s;
      if (t2 != NULL) {
	s= t2;
#ifdef CLASSIC_MODE
        s->setHight(idxPoint.getHight());
#endif
	t2= NULL;
      } else {
	haveMorePolygons= false;
      }
    }

    cadModel->next();
  }
  return color;
}

// EOF: src/generator/oct_gen.cpp

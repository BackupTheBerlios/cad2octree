/**
 * file: src/geom/node_vec.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <node_vec.h>

#include <exception.h>

// ##### NodeVec() ###################################################
NodeVec::NodeVec(NodeIndex nodeIdx) : NodeIndex(nodeIdx) {}

// ##### NodeVec() 
NodeVec::NodeVec(NodeVec pStart, NodeVec pEnd) : NodeIndex(pEnd - pStart) {
  assert (pStart.getHight() == pEnd.getHight());
}

// ##### getDirection() ##############################################
Direction NodeVec::getDirection() {
  return Direction(SIGN(getX()), SIGN(getY()), SIGN(getZ()));
}

// ##### operator- ###################################################
NodeVec operator-(NodeVec p1, NodeVec p2) {
  assert (p1.getHight() == p2.getHight());
  
  return NodeIndex(p1.getX() - p2.getX(), 
                   p1.getY() - p2.getY(), 
		   p1.getZ() - p2.getZ(),
		   p1.getHight());
}

// EOF: src/geom/node_vec.cpp

/**
 * @file src/generator/oct_gen.h
 * Oktalbaumgenerator.
 *
 * Erstellt unter Zuhilfenahme des CadModel einen Oktalbaum.
 * OctGen bildet somit die Schnittstelle zwischen CadModel und der
 * Oktalbaumstruktur. 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen" \n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __OCT_GEN_H__
#define __OCT_GEN_H__

#include <cad/cad_model.h>
#include <generator/gen_help.h>
#include <octree/index_oct.h>

#include <node_index.h>
#include <exception.h>

// ##### Exceptions ##################################################
/**
 * Das CadModel enth�lt keine Geometriedaten oder die Geometriedaten
 * bilden keine 3D-Objekte (z.B. spannt 
 * (CadModel::getMinPoint(); CadModel::getMaxPoint()) keinen K�rper auf)
 */
class WrongModelException : Exception {
 public:
  /**
   * Exception-Konstruktor.
   */
  WrongModelException() : Exception("Wrong CadModel") {}
};

// ###### OctGen #####################################################
/**
 * Oktalbaumgenerator.
 *
 * Erstellt unter Zuhilfenahme des CadModel einen Oktalbaum.
 * OctGen bildet somit die Schnittstelle zwischen CadModel und der
 * Oktalbaumstruktur. 
 */
class OctGen {
 public:
  /**
   * Konstruktor.
   * @param model zur Generierung verwendetes CadModel
   */
  OctGen(CadModel* model);

  /**
   * F�gt den Punkts p mit der Farbe color in den Oktalbaum ein.
   * @param p Knotenindex des Punkts
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren. 
   */
  void add(NodeIndex p, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * F�gt das Viereck pApBpCpD
   * mit der Farbe color in den Oktalbaum ein.
   * @param pA Knotenindex des Viereckpunkts A
   * @param pB Knotenindex des Viereckpunkts B
   * @param pC Knotenindex des Viereckpunkts C
   * @param pD Knotenindex des Viereckpunkts D
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              neue Oktalbaumstrukturteile zu allozieren. 
   * @pre pA.getHight() = pB.getHight() = pC.getHight() = pD.getHight()
   */
  void addQuadrilateral(NodeIndex pA, NodeIndex pB, NodeIndex pC,
		        NodeIndex pD, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * F�gt das Dreieck \f$ \triangle p_Ap_Bp_C \f$
   * mit der Farbe color in den Oktalbaum ein.
   * @param pA Knotenindex des Dreieckspunkts A
   * @param pB Knotenindex des Dreieckspunkts B
   * @param pC Knotenindex des Dreieckspunkts C
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              neue Oktalbaumstrukturteile zu allozieren. 
   * @pre pA.getHight() = pB.getHight() = pC.getHight()
   */
  void addTriangle(NodeIndex pA, NodeIndex pB, NodeIndex pC,
		   Color color)
    throw (NotEnoughMemoryException*);

  /**
   * Liefert das zur Oktalbaumgenerierung genutzte CadModel.
   * @return CadModel
   * @post return != NULL
   */
  CadModel* getCadModel();

#ifndef CLASSIC_MODE
  /**
   * Liefert die Farbe des Knotens p, die unter Zuhilfenahme des CadModel
   * ermittelt wurde.
   * @param p Knoten-Index
   * @return NO_OBJECT, falls sich p au�erhalb eines K�rpers befindet
   *         und ansonsten die Farbe des Knotens einer 'Nachbarfl�che'
   *         (entspricht der K�rperfarbe)
   * @pre cadModel != NULL
   */
  Color getColor(NodeIndex p);
#endif

  /**
   * Liefert das Hilfsobjekt zur Oktalbaumgenerierung.
   * @return GenHelp
   * @post return != NULL
   */
  GenHelp* getGenHelp();

  /**
   * Liefert den Oktalbaum, der f�r die Generierung verwendet wird.
   * @return Oktalbaum
   */
  IndexOct* getGenTree();

  /**
   * Generiert unter Nutzung des CadModel einen Oktalbaum mit
   * maximaler Baumh�he maxTreeHight.
   * @param maxTreeHight maximale Baumh�he
   * @return generierter Oktalbaum
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren.
   * @exception WrongModelException Das zugrundeliegende CadModel ist
   *              ung�ltig (vgl. checkModel()).
   */
  IndexOct* getOctree(Hight maxTreeHight)
    throw (NotEnoughMemoryException*, WrongModelException*);

 private:
  /**
   * F�gt die Strecke \f$\over{\mbox{pA pB}} \f$
   * mit der Farbe color in den Oktalbaum ein.
   * @param start Knotenindex des Streckenanfangspunkts
   * @param end Knotenindex des Streckenendpunkts
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren. 
   * @pre start.getHight() = end.getHight()
   */
  void addLine(NodeIndex start, NodeIndex end, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * F�gt das CadObject object
   * mit der Farbe color in den Oktalbaum ein.
   * @param object CadObject
   * @param color Farbe
   * @exception NotEnoughMemoryException Nicht gen�gend Speicher, um
   *              die neue Oktalbaumstruktur zu allozieren. 
   * @pre object != NULL
   */
  void addObject(CadObject* object, Color color)
    throw (NotEnoughMemoryException*);

  /**
   * �berpr�ft, ob das cadModel g�ltig ist.
   * Falls es nicht g�ltig ist wird eine WrongModelException
   * geworfen.
   * @exception WrongModelException
   *    cadModel == NULL or else cadModel->empty()
   *    or else not cadModel->getMinPoint() << cadModel->getMaxPoint()
   */
  void checkModel() throw (WrongModelException*);

  /**
   * Liefert, NO_OBJECT, falls sich p au�erhalb eines K�rpers befindet
   *          und ansonsten die Farbe des Knotens einer 'Nachbarfl�che'
   *          (entspricht der K�rperfarbe)
   * ermittelt wurde. Es wird die n�chster-Punkt-Methode verwendet.
   * @param p Knoten-Index
   * @return Farbe des Knotens p
   * @pre cadModel != NULL
   * @pre p.getHight() = BASE_NODE_HIGHT
   */
  Color nextPointColor(NodeIndex p);

#ifndef CLASSIC_MODE
  /**
   * Liefert NO_OBJECT, falls sich p au�erhalb eines K�rpers befindet
   *         und ansonsten die Farbe des Knotens einer 'Nachbarfl�che'
   *         (entspricht der K�rperfarbe)\n
   * Es wird die Testraymethode verwendet.
   * @param p Knoten-Index
   * @return Farbe des Knotens p
   * @pre cadModel != NULL
   * @pre p.getHight() = BASE_NODE_HIGHT
   * @pre RAY_AXIS < DIMENSIONS
   * @pre RAY_DIR = BACKWARD or RAY_DIR = FORWARD
   */
  Color testRayColor(NodeIndex p);
#else

  void generateClassic(NodeIndex idx);

  /**
   * Liefert NO_OBJECT, falls sich p au�erhalb eines K�rpers befindet
   *         und ansonsten die Farbe des Knotens einer 'Nachbarfl�che'
   *         (entspricht der K�rperfarbe)\n
   * Es wird die Testraymethode verwendet.
   * @param p Knoten-Index
   * @param isAtBorder Wird gesetzt, falls sich p auf der Oberflache eines 
   *                   K�rpers befindet.
   * @return Farbe des Knotens p
   * @pre cadModel != NULL
   * @pre RAY_AXIS < DIMENSIONS
   * @pre RAY_DIR = BACKWARD or RAY_DIR = FORWARD
   */
  Color testRayColor(NodeIndex p, bool &isAtBorder);
#endif

  /**
   * Zur Generierung verwendetes CadModel.
   */
  CadModel* cadModel;

  /**
   * Hilfsobjekt f�r die Generierung der Oktalbaumstruktur.
   */
  GenHelp* genHelp;

  /**
   * Oktalbaum, in den die Punkte generiert werden sollen.
   */
  IndexOct* octree;
};

#endif // ! __OCT_GEN_H__

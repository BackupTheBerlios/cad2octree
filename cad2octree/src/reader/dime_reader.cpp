/**
 * file: src/reader/dime_reader.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <reader/dime_reader.h>

#include <iostream>

#include <dime/Input.h>

// ##### DimeReader() ################################################
DimeReader::DimeReader(const char* dxfFile) 
    throw (ReadFileException*, FileFormatException*) {
  model= NULL;

  dimeInput input;
  if (!input.setFile(dxfFile)) {
    throw new ReadFileException(dxfFile);
  }

  model= new dimeModel();
  
  if (!model->read(&input)) {
    delete model;
    throw new FileFormatException(getFormatName(),
			          dxfFile, input.getFilePosition());
  }
}

// ##### ~DimeReader() ###############################################
DimeReader::~DimeReader() {
  if (model != NULL) {
    delete model;
  }
}

// ##### generateCadModel() ##########################################
bool DimeReader::generateCadModel(const dimeState* const state,
				  dimeEntity *entity, void *data) {
  assert (data != NULL);

  if (entity == NULL) {
    return false;
  }

  DimeHelp* dimeHelp= (DimeHelp *)data;
  dimeHelp->add(entity);
  return true;
}

// ##### getCadModel() ###############################################
CadModel* DimeReader::getCadModel(Color color, bool splitQuad) {
  DimeHelp* dimeHelp= new DimeHelp(new CadModel(), color, splitQuad);
  getDimeModel()->traverseEntities(generateCadModel, dimeHelp);
  return dimeHelp->getCadModel();
}

// ##### getDimeModel() ##############################################
/**
 * @pre model != NULL
 */
dimeModel* DimeReader::getDimeModel() {
  assert (model != NULL);

  return model;
}

// ##### getFileFormatVersion() ######################################
const char* DimeReader::getFileFormatVersion() {
  const char* ver= getDimeModel()-> getDxfVersion();
  return ( ver != NULL ? ver : "unknown" );
}

// ##### getLibVersion ###############################################
const char* DimeReader::getLibVersion() {
  return dimeModel::getVersionString();
}

// ##### dimeParam2str() #############################################
const char* DimeReader::dimeParam2str(dimeParam param, int groupCode) {
  char buf[STR_LEN];

  buf[0] = 0;

  if (groupCode < 10) {
    sprintf(buf, "%s", param.string_data);
  } else if (groupCode < 60) {
    sprintf(buf, "%f", param.double_data);
  } else if (groupCode < 80) {
    sprintf(buf, "%d", param.int16_data);
  } else if (groupCode < 100) {
    sprintf(buf, "%d", param.int32_data);
  } else if (groupCode < 110) {
    sprintf(buf, "%s", param.string_data);
  } else if (groupCode < 160) {
    sprintf(buf, "%f", param.double_data);
  } else if (groupCode < 200) {
    sprintf(buf, "%d", param.int16_data);
  } else if (groupCode < 240) {
    sprintf(buf, "%f", param.double_data);
  } else if (groupCode < 290) {
    sprintf(buf, "%d", param.int16_data);
  }
  return strdup(buf);
}

// ##### print() #####################################################
void DimeReader::print() {
  cout << "Dime-Version is " << getLibVersion() << endl;
  cout << "DXF-File Version is " << getFileFormatVersion() << endl << endl;
  
  cout << "Entities" << endl;
  cout << "========" << endl;
  getDimeModel()-> traverseEntities(printEntity, NULL, false, true, true);
}

// ##### printEntity() ###############################################
bool DimeReader::printEntity(const dimeState* const state,
			    dimeEntity *entity, void *data) {
  const char* DIME_Types[] =  {"???",
    "Base",
    "Record",
    "StringRecord",
    "FloatRecord",
    "DoubleRecord",
    "Int8Record",
    "Int16Record",
    "Int32Record",
    "HexRecord",
    "RecordHolder",
    "Class",
    "UnknownClass",
    "Object",
    "UnknownObject",
    "Entity",
    "UnknownEntity",
    "Polyline",
    "Vertex",
    "FaceEntity",
    "ExtrusionEntity",
    "3DFace",
    "Solid",
    "Trace",
    "Line",
    "Point",
    "Block",
    "Insert",
    "Circle",
    "Arc",
    "LWPolyline",
    "Ellipse",
    "Spline",
    "Section",
    "UnknownSection",
    "EntitiesSection",
    "BlocksSection",
    "TablesSection",
    "HeaderSection",
    "ClassesSection",
    "ObjectsSection",
    "Table",
    "TableEntry",
    "UnknownTable",
    "UCSTable",
    "LayerTable",
    ":LastType"
  };
  if (entity == NULL) {
    cout << "### Wrong Entity ###" << endl;
    return false;
  }
  cout << entity->getEntityName() << " [(" << entity->typeId() << ")"; 
  cout << DIME_Types[entity->typeId()] << "]";
  cout << "  Color = " << entity->getColorNumber() << endl;
  entity-> print();
  cout << endl;
  return true;
}

// EOF src/reader/dime_reader.cpp

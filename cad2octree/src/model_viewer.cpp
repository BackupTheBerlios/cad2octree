/**
 * @file src/model_viewer.cpp
 * Hauptdatei zur CadModel-Anzeige.
 *
 * Gibt die Geometriedaten der CAD-Datei aus.
 * Dazu wird ein Reader verwendet.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <iostream>

#include <reader/reader.h>
#include <cad/cad_model.h>

/**
 * Schreibt ein Hilfstext zur Verwendung (Aufrufparameter) auf die
 * die Konsole.
 */
void usage() {
  cout << "model_viewer [-q] <dxf-file>" << endl;
  cout << "-q           Split all Quadrilaterals from input-file " << endl;
  cout << "             into 2 triangles." << endl;
  cout << "input-file   dxf-File to read." << endl;
}

/**
 * Liest die Datei fileName ein und gibt die in ihr enthaltenen 
 * Geometriedaten auf der Konsole aus.
 * @param fileName Dateiname
 * @param splitQuad Ob alle Vierecke in 2 Dreiecke geteilt werden sollen.
 * @return -1, falls die Datei nicht gelesen werden konnte (Lesefehler,
 *             falsches Format)\n
 *          0, ansonsten
 */
int read(const char* fileName, bool splitQuad) throw() {
  int readError= 0;
  try {
    Reader* reader= Reader::readFile(fileName);
    assert (reader != NULL);
    reader->print();
    cout << endl << endl;
    CadModel* cadModel= reader->getCadModel(1, splitQuad);
    assert (cadModel != NULL);
    cadModel->print();
  } catch (Exception* e) {
    if (e == NULL) {
      cerr << "Upps... Something is wrong :-(" << endl;
      readError= -1;
    }
    cerr << e->getMsg() << endl;
    readError= -1;
  } catch (...) {
    cerr << "Upps... Something is wrong :-(" << endl;
    readError= -1;
  }
  return readError;
}

/**
 * Hauptfunktion.
 * @return -1, falls ein Fehler auftritt\n
 *          0, ansonsten
 */
int main(int argc, char *argv[]) {
  const char* inFile= NULL;
  bool splitQuad= false;

  for (int i= 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if (inFile != NULL) {
	usage();
	return -1;
      }
      inFile = argv[i];
    }
    else {
      switch (argv[i][1]) {
      case 'q':
        splitQuad= !splitQuad;
	break;
      default:
        usage();
	return -1;
      }
    }
  }

  if (inFile == NULL ) {
    usage();
    return -1;
  }

  read(inFile, splitQuad);
  return 0;
}

// EOF: src/model_viewer.cpp

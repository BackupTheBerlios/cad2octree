/**
 * @file src/geom_test.cpp
 * Zur Überprüfung des geometrischen Modells.
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <generator/oct_gen.h>
#include <writer/writer.h>
#include <filename.h>

/**
 * Maximaltiefe des Oktalbaums, falls keine andere Maximaltiefe
 * an der Kommandozeile festgelegt wird.
 */
#define STD_MAX_DEPTH 6

/**
 * Schreibt ein Hilfstext zur Verwendung (Aufrufparameter) auf die
 * die Konsole.
 */
int usage(const char* progname) {
  cout << progname << " [-d depth] -o output-file" << endl;
  cout << "-d depth      Maximum depth of to generate octree" << endl;
  cout << "              It can be between [2; " << MAX_HIGHT << "]" << endl;
  cout << "              Default is " << STD_MAX_DEPTH << endl;
  cout << "output-file   pot-File to write." << endl;
  return 1;
}

/**
 * Liefert ein Triangle, in dem alle 3 Eckpunkte die Koordinaten von p
 * haben.
 * @param p Point
 * @return Dreieck ppp :-)
 */
Triangle* getTriangle(Point p) {
  return new Triangle(p, p, p);
}

/**
 * Liefert ein CadModel.
 * @return CadModel
 */
CadModel* getCadModel() {
  CadModel* model= new CadModel();
  assert (model != NULL);
  model->add(getTriangle(Point(0, 0, 0)), 1);
  model->add(getTriangle(Point(1, 1, 1)), 1);

  model->add(new Triangle(Point(0.5, 0, 0), Point(0, 0.5, 0),
			  Point(0, 0, 0.5)), 1);
  model->add(new Triangle(Point(0.25, 0, 0), Point(0, 0.75, 0.75),
			  Point(0.75, 1, 1)), 1);
  return model;
}

/**
 * Erzeugt aus einfachen 
 * Geometriedaten den Oktalbaum mit Maximaltiefe depth und
 * schreibt ihn in outFile.
 * @param outFile zu schreibende Datei
 * @param maxTreeHight Maximaltiefe des zu generierenden Oktalbaums
 * @return \em -1, falls etwas schief ging (Lesefehler,
 *                 falsches Format, nicht genügend Speicher, Schreibfehler)\n
 *         \em  0, ansonsten
 */
int convert(const char* outFile, Hight maxTreeHight)
    throw() {
  int error= 0;
  try {
    cerr << "Erzeugen des CadModel ..." << endl;
    CadModel* cadModel= getCadModel();
    cerr << "Erzeugen der Oktalbaumstruktur ..." << endl;
    OctGen* octGen= new OctGen(cadModel);
    assert (octGen != NULL);
    IndexOct* octree= octGen->getOctree(maxTreeHight);
    delete octGen;
    delete cadModel;
    assert (octree != NULL);
    cerr << "Schreiben von " << outFile << " ..." << endl;
    Writer* writer= Writer::getWriter(outFile);
    assert (writer != NULL);
    writer->writeFile(octree);
    cerr << outFile << " geschrieben." << endl;
    delete writer;
    cerr << "Fertig!" << endl;
  } catch (Exception* e) {
    if (e == NULL) {
      cerr << "Upps... Something is wrong :-(" << endl;
      return -1;
    }
    cerr << e->getMsg() << endl;
    error= -1;
  } catch (...) {
    cerr << "Upps... Something is wrong :-(" << endl;
    error= -1;
    }
  return error;
}

/**
 * Hauptfunktion.
 * @return -1, falls ein Fehler auftrat\n
 *          1, falls die Hilfe angezeigt wurde\n
 *          0, ansonsten
 */
int main(int argc, char *argv[]) {
  const char* outFile= NULL;
  int hight= STD_MAX_DEPTH;

  for (int i= 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      return usage(argv[0]);
    }
    else {
      switch (argv[i][1]) {
      case 'o':
	i++;
	if (i >= argc || outFile != NULL) {
	  return usage(argv[0]);
	}
	outFile = argv[i];
	break;
      case 'd':
	i++;
	if (i >= argc) {
	  return usage(argv[0]);
	}
	if (atoi(argv[i]) <= 1 || atoi(argv[i]) > MAX_HIGHT) {
	  return usage(argv[0]);
	}
	hight = atoi(argv[i]);
	break;
      default:
	return usage(argv[0]);
      }
    }
  }

  if (outFile == NULL) {
    return usage(argv[0]);
  }

  return convert(outFile, hight);
}

// EOF: src/geom_test.cpp

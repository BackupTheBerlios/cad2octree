/**
 * @file src/fulltree.cpp
 * Hauptdatei zur Generierung eines vollst�ndig besetzen Oktalbaums.
 * Der Baum besitzt also ausschlie�lich innere Knoten auf allen au�er
 * der untersten Ebene; auf unterster Ebene befinden
 * sich \f$ 2^{\mbox{maxTreeHight}} \f$ Bl�tter, die als im K�rper befindend
 * (also mit flag 1) markiert sind. 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */

#include <iostream>

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
  cout << progname << " [-d depth] [output-file]" << endl;
  cout << "-d depth     Maximum depth of to generate octree" << endl;
  cout << "             It can be between [2; " << MAX_HIGHT << "]" << endl;
  cout << "             Default is " << STD_MAX_DEPTH << endl;
  cout << "output-file  pot-File to write." << endl;
  cout << "             Default is 'fulltree_<depth>.pot'" << endl;
  return 1;
}

/**
 * Generiert einen vollst�ndig besetzten Oktalbaum der H�he h. 
 * Die Bl�tter sind als im K�rper befindend (also mit flag 1) markiert.
 * @param h Tiefe des zu generierenden Oktalbaums
 * @return \em -1, falls etwas schief ging
 *                 (nicht gen�gend Speicher)\n
 *         \em  0, ansonsten
 * \note Die automatische Kompaktierung muss ausgeschaltet sein!
 */
IndexOct* generateTree(Hight h) {
  int max= (1<<h) - 1;
  IndexOct* octree= new IndexOct(h);
  if (octree == NULL) {
    throw NotEnoughMemoryException();
  }

  for (int z= 0; z <= max; ++z) {
    for (int y= 0; y <= max; ++y) {
      for (int x= 0; x <= max; ++x) {
	octree->add(NodeIndex(x, y, z), 1);
      }
    }
    if (max > 50) {
      printf("Fortschritt %d%%%c", 13, (100*z)/max);
    }
  }
  cout << endl;
  
  return octree;
}

/**
 * Generiert einen vollst�ndig besetzten Oktalbaum der H�he treeHight und
 * schreibt ihn in outFile.
 * @param outFile zu schreibende Datei
 * @param treeHight Tiefe des zu generierenden Oktalbaums
 * @return \em -1, falls etwas schief ging
 *                 (falsches Format, nicht gen�gend Speicher, Schreibfehler)\n
 *         \em  0, ansonsten
 */
int make(const char* outFile, Hight treeHight)
    throw() {
  int error= 0;
  try {
    cout << "Generiere Oktalbaum der Tiefe " << (int)treeHight
	 << " ..." << endl;
    IndexOct* octree= generateTree(treeHight);
    assert (octree != NULL);
    cout << "Schreiben von " << outFile << " ..." << endl;
    Writer* writer= Writer::getWriter(outFile);
    assert (writer != NULL);
    writer->writeFile(octree);
    cout << outFile << " geschrieben." << endl;
    cout << "R�ume auf ..." << endl;
    delete octree;
    delete writer;
    cout << "Fertig!" << endl;
  } catch (Exception* e) {
    if (e == NULL) {
      cout << "Upps... Something is wrong :-(" << endl;
      error= -1;
    }
    cout << e->getMsg() << endl;
    error= -1;
  } catch (...) {
    cout << "Upps... Something is wrong :-(" << endl;
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
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
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
      case 'o':
        i++;
	if (i >= argc) {
	  return usage(argv[0]);
	}
        if (outFile != NULL) {
	  return usage(argv[0]);
        }
        outFile = argv[i];
        break;
      default:
	return usage(argv[0]);
      }
    }
  }

  if (outFile == NULL) {
    char outName[100];
    sprintf(outName, "fulltree_%d.pot", hight);
    outFile= strdup(outName);
  }

  return make(outFile, hight);
}

// EOF: src/fulltree.cpp

/**
 * @file src/cad2octree.cpp
 * \b Hauptdatei zur Oktalbaumstruktur-Generierung.
 *
 * Erzeugt unter Verwendung der DXF-Daten eine Oktalbaumstruktur. 
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"
 * @author Stefan Mahler
 * @date 2002
 */
/**
 * \mainpage
 * \section Codebeschreibung cad2octree
 * Implementierung zur Diplomarbeit <em> "Erzeugung und Evaluierung von
 * Oktalbaumstrukturen als Schnittstelle zu CAD-Programmen" </em>
 * Diplomarbeit-Nr. 2035
 *
 * Mit Hilfe dieses Programms können Geometrieinformationen aus
 * gültigen DXF (Drawable Exchange Format) - Dateien extrahiert werden.
 * Diese Daten werden zur Erzeugung einer Octree-Struktur verwendet.
 *
 * - Autor: Stefan Mahler
 * - Betreuer: Ralf-Peter Mundani
 * - erstellt: 2002\n
 * Abteilung Simulation großer Systeme, Institut für Informatik, 
 * Universität Stuttgart
 *
 * \note Zum Einlesen des DXF-Formats wird die GPL-Bibliothek 
 *   Dime Version 0.9.1 verwendet. 
 *   Beachten sie die in der Datei \em LICENCE beschriebenen Richtlinien.
 */

#include <iostream>

#include <reader/reader.h>
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
  cout << progname << " [-q] [-d depth] input-file -o output-file" << endl;
  cout << "-q               Split all Quadrilaterals from input-file" << endl;
  cout << "                 into 2 triangles." << endl;
  cout << "-d depth         Maximum depth of to generate octree" << endl;
  cout << "                 It can be between [2; " << MAX_HIGHT << "]"<< endl;
  cout << "                 Default is " << STD_MAX_DEPTH << endl;
  cout << "input-file       dxf-File to read." << endl;
  cout << "-o output-file   pot-File to write." << endl;
  return 1;
}

/**
 * Liest die Datei inFile ein, generiert aus den enthaltenen 
 * Geometriedaten den Oktalbaum mit Maximaltiefe depth und
 * schreibt ihn in outFile.
 * @param inFile  einzulesende Datei
 * @param outFile zu schreibende Datei
 * @param maxTreeHight Maximaltiefe des zu generierenden Oktalbaums
 * @param splitQuad Ob alle Vierecke des Eingabemodells als 2 Dreiecke im 
 *                  cadModel repräsentiert werden sollen.
 * @return \em -1, falls etwas schief ging (Lesefehler,
 *                 falsches Format, nicht genügend Speicher, Schreibfehler)\n
 *         \em  0, ansonsten
 */
int convert(const char* inFile, const char* outFile, 
	    Hight maxTreeHight, bool splitQuad)
    throw() {
  int error= 0;
  try {
    cerr << "Einlesen von " << inFile << " ..." << endl;
    Reader* reader= Reader::readFile(inFile);
    assert (reader != NULL);
    cerr << "Extrahieren der Geometriedaten ..." << endl;
    CadModel* cadModel= reader->getCadModel(1, splitQuad);
    delete reader;
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
  const char* inFile= NULL;
  const char* outFile= NULL;
  int hight= STD_MAX_DEPTH;
  bool splitQuad= false;

  for (int i= 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if (inFile != NULL) {
	return usage(argv[0]);
      }
      inFile = argv[i];
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
      case 'q':
        splitQuad= !splitQuad;
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

  if (inFile == NULL ) {
    return usage(argv[0]);
  }

  if (outFile == NULL) {
    string outName= getPurName(inFile);
    outName+= ".pot";
    outFile= outName.c_str();
  }

  return convert(inFile, outFile, hight, splitQuad);
}

// EOF: src/cad2octree.cpp

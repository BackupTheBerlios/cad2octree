/**
 * @file src/utils/global.h
 * enth�lt allgemeine Definition, wie globale Konstanten
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universit�t Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <limits.h>

using namespace std;

/**
 * assert-check ausschalten
 */
#define NDEBUG

/**
 * Nutze den 'klassischen' Baumerzeugungsalgorithmus.
 */
//#define CLASSIC_MODE

/**
 * F�lle K�rper. Ist dies ausgeschaltet, werden nur die Oberfl�chen der
 * K�rper generiert.
 */
#define FILL_SOLIDS

/**
 * Nutze einen der IsIn-Polygon-Agorithmen
 */
//#define ALGORITHM_ISIN

/**
 * Nutze den det-check-Algorithmus f�r Polygon::isInPlane()
 */
//#define ALGORITHM_CHECK_DET

/**
 * Zur Lokalisation von Punkten (z.B. beim F�llen) gegen�ber Splines
 * wird nur das Kontrollpunktnetz verwendet.
 */
//#define CHK_CP_ONLY

/**
 * Zur Lokalisaton von Punkten (z.B. beim F�llen) gegen�ber Splines
 * werden wird nur das aus Oberfl�chenpolygonen erzeugte Netz verwendet.
 * @note Es sollte nicht gleichzeitig CHK_CP_ONLY ein- und EXTRACT_PART
 * ausgeschaltet sein!  (Wohl aber k�nnen beide eingeschaltet sein.)
 */
//#define EXTRACT_PART

/**
 * Zur Dreiecksfl�chengenerierung wird bei der isIn-�berpr�fung auf 
 * den ccw-Check der zweidimensionalen Projektion zur�ckgegriffen.
 * @pre Polygon::getCount() == 3
 */
//#define CCW_CHECK

/**
 * In ScanLine ist es m�glich gleichzeitig auf mehreren Achsen weiterzugehen 
 * (und so direkt zum 'diagonalen' Nachbarn als n�chsten Punkt zu gehen).
 */
//#define COMB_SCAN_LINE

/**
 * Sichere Bestimmung der F�llfarbe. 
 *
 * Bei F�llausangspunkten der untersten Ebene werden auch die Nachbarpunkte 
 * in die F�llfarbbestimmung einbezogen. 
 */
//#define SAVED_FILL

/**
 * Anstatt eines Stacks wird eine Queue benutzt. MARK_BORDER, LIMITED_STACK 
 * und MAX_RECURSIVE_DEEP haben eine analoge Wirkung. 
 */
#define USE_QUEUE

/**
 * Setzt die Knoten, die bei MAX_RECURSIVE h�tten gef�llt werden m�ssen,
 * auf eine Randfarbe, aus der die 'richtige' Farbe wieder konstruiert werden
 * kann. Das F�llen kann dann ab diesen Knoten mit leeren Stack wieder
 * begonnen werden. Dieser Schalter stellt eine Alternative
 * zu LIMITED_STACK dar. Dieser Schalter ist nur dann relevant, falls
 * der Schlater FILL_SOLIDS eingeschaltet ist.
 */
//#define MARK_BORDER

/**
 * Begrenzung des Aufrufstapels von FillOct::fillNext(). Dieser Schalter
 * ist nur relevant, falls der Schalter FILL_SOLIDS eingeschaltet ist.
 * Ist der Schalter eingeschaltet, wird maximal MAX_RECURSIVE_DEEP Mal
 * FillOct::fillNext() ineinander aufgerufen.
 */
//#define LIMITED_STACK

/**
 * Zur Ermittlung der F�llfarbe wird die Strahlmethode verwendet.
 */
#define RAY_METHODE

/**
 * Wieviele Nachbarn beim F�llen mit gef�llt werden (wenn sie im gleichen
 * Bereich liegen). Dieser Wert ist f�r besonders gro�e Bereiche relevant.
 * Je h�her dieser Wert, desto schneller k�nnen gro�e Bereiche gef�llt
 * werden, aber desto mehr Stapel-Speicher wird auch ben�tigt.
 * Der Schalter ist nur dann relevant, wenn die Schalter FILL_SOLIDS
 * und ( MARK_BORDER oder LIMITED_STACK ) eingeschaltet sind.
 */
#define MAX_RECURSIVE_DEEP 65000

/**
 * Maximales Abstandsquadrat zweier Vektoren, so dass sie bei ALGORITHM_ISIN
 * als identisch angesehen werden
 */
#define VEC_ABS_MAX 0.75

/**
 * Maximum bei ALGORITHM_CHECK_DET, bei dem der Punkt noch als zur Ebene 
 * geh�rend betrachtet wird. 
 */
#define DET_MAX 0.5

/**
 * Anzahl der Dimensionen des Cad-Models bzw. der Octree-Struktur.
 */
#define DIMENSIONS 3

/**
 * Anzahl der Begrenzungspunkte einer Fl�che.
 * @see Plane
 * @see 3DFace im DXF-Format
 */
#define COUNT_VERTEX_IN_FACE 4

/**
 * Gr��tm�gliche Tiefe des Oktalbaums. 
 *
 * Ergibt sich aus dem Wertebereich der Typen zur Bearbeitung 
 * von Knoten-Indizes und Punkten, also AxIndex und Coordinate.
 */
#define ABSOLUTE_MAX_DEPTH ( (8*sizeof(int) - 1) / 2 )

/**
 * Abstand zweier Flie�kommazahlen, ab dem sie nicht mehr als gleich
 * aufgefasst werden.
 */
#define EPSILON 1e-8

/**
 * Maximum zweier Zahlen
 */
#define MAX(x1, x2) ((x1) > (x2) ? (x1) : (x2))

/**
 * Minimum zweier Zahlen
 */
#define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))

/**
 * Standard-Maximall�nge von Stringpuffern 
 */
#define STR_LEN 1024

/**
 * Teststrahl parallel zur x-Achse
 * @see OctGen::testRay()
 * @see OctGen::testLine()
 */
#define RAY_AXIS X_AXIS 

/**
 * Teststrahl verl�uft in Richtung +Unendlich 
 * @see OctGen::testRay()
 */
#define RAY_DIR FORWARD

/**
 * Typ f�r Punkt- bzw. Vektorkoordinaten
 */
typedef double Coordinate;

/**
 * Koordinaten-Achsen
 */
typedef int Axis;

#ifdef COMB_SCAN_LINE
/**
 * Kombination auf mehreren Achsen
 */
typedef int AxComb;
#endif

/**
 * X-Achse
 */
const Axis X_AXIS= 0;

/**
 * Y-Achse
 */
const Axis Y_AXIS= 1;

/**
 * Z-Achse
 */
const Axis Z_AXIS= 2;

/**
 * Typ f�r die Baumh�he.
 * Aus der Maximalbaumh�he resultiert die Maximalgenauigkeit der Darstellung.
 *
 * Es gilt:
 * - hight des Wurzelknotens = maxTreeHight des Baumes
 * - hight eines Blattknotens der 'untersten Ebene' = 0
 */
typedef int Hight;

/**
 * Gr��tm�gliche Maximaltiefe
 */
const Hight MAX_HIGHT= ABSOLUTE_MAX_DEPTH;

/**
 * Typ f�r K�rperfarbe
 */
typedef int Color;

/**
 * 'Gr��te' Farbe.
 */
const Color MAX_COLOR= INT_MAX - 1;

/**
 * Liefert den Absolutbetrag von x:\n
 *  x, falls x >= 0\n
 * -x, sonst
 */
Coordinate ABS(Coordinate x);

/**
 * Zum Vergleich zweier Koordinaten auf Gleichheit
 */
bool EQUIVAL(Coordinate coord1, Coordinate coord2);

/**
 * Vorzeichen von x:\n
 *  1, falls x > 0\n
 * -1, falls x < 0\n
 *  0, sonst
 */
int SIGN(Coordinate x);

/**
 * Liefert i in 3-er Bl�cken zur�ck.
 * @param i Zahl
 * @return 'i' formatiert.
 */
char* formatLarge(unsigned i);

#endif // ! __GLOBAL_H__

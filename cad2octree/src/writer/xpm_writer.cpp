/**
 * file: src/writer/xpm_writer.cpp
 *
 * Diplomarbeit Nr. 2035 - "Erzeugung und Evaluierung von Oktalbaumstrukturen
 * als Schnittstelle zu CAD-Programmen"\n
 * SgS, Universität Stuttgart
 * @author Stefan Mahler
 * @date 2002
 */

#include <writer/xpm_writer.h>
#include <filename.h>

/**
 * Zeichen für einen Körper-Voxel.
 */
#define IS_OBJ_COLOR_CHAR '*'

/**
 * Zeichen für einen Voxel, der keinen Körper.
 */
#define NO_OBJ_COLOR_CHAR ' '

// ##### XpmWriter() #################################################
XpmWriter::XpmWriter(const char* fileName)
  : extension(getExtension(fileName)), fileName(getPurName(fileName)) {
}

// ##### ~XpmWriter() ################################################
XpmWriter::~XpmWriter() {
  if (out.is_open()) {
    out.close();
  }
}

// ##### getColorChar() ##############################################
char XpmWriter::getColorChar(AxIndex h, AxIndex i[2]) {
  assert (DIMENSIONS == 3);
  assert (0 <= sectAxis && sectAxis < DIMENSIONS);

  AxIndex coord[3];
  int iAxis= 0;
  for (Axis axis= 0; axis < 3; ++axis) {
    if (axis == sectAxis) {
      coord[axis]= h;
    } else {
      coord[axis]= i[iAxis];
      ++i;
    }
  }

  NodeIndex p= NodeIndex(coord[0], coord[1], coord[2], BASE_NODE_HIGHT);
  p= octree->getExistNode(p);
  Color color= octree->getColor(p);
  assert (color > UNDEF_OBJ);
  return (color == NO_OBJECT ? NO_OBJ_COLOR_CHAR : IS_OBJ_COLOR_CHAR);
}

// ##### getFileName() ###############################################
const char* XpmWriter::getFileName(int number) {
  string pre= fileName;
  char buf[31];
  char axNum[2];
  axNum[0]= (char)(sectAxis + 'x');
  axNum[1]= (char)0;
  sprintf(buf, "_%s%.3d.", axNum, number);
  return strdup((pre+buf+string(extension)).c_str());
}

// ##### getFormatName() #############################################
const char* XpmWriter::getFormatName() {
  return "XPM";
}

// ##### getFormatType() #############################################
const Writer::FormatType XpmWriter::getFormatType() {
  return XPM;
}

// ##### getWidth() ##################################################
AxIndex XpmWriter::getWidth() {
  return 1 << octree->getMaxTreeHight();
}

// ##### write() #####################################################
void XpmWriter::write(char colorChar) {
  out << colorChar;
}

// ##### writeFooter() ###############################################
void XpmWriter::writeFooter() {
  out << "};" << endl;
}

// ##### writeHeader() ###############################################
void XpmWriter::writeHeader(int number) {
  out << "/* XPM */" << endl;
  out << "static char *cad2octree_XpmWriterFile_" << (char)(sectAxis + 'x')
      << number << "[]= {" << endl;
  out << '"' << getWidth() << " " << getWidth() << " 2 1" << '"' << ","
      << endl;
  out << "/* columns rows colors chars-per-pixel */" << endl;
  out << '"' << NO_OBJ_COLOR_CHAR << " m white c white " << '"' << "," << endl;
  out << '"' << IS_OBJ_COLOR_CHAR << " m black c black " << '"' << "," << endl;
  out << "/* pixels */" << endl;
}

// ##### writeLineBegin() ############################################
void XpmWriter::writeLineBegin() {
  out << '"';
}

// ##### writeLineEnd() ##############################################
void XpmWriter::writeLineEnd(bool isLast) {
  out << '"';
  if (!isLast) {
    out << "," << endl;
  }
}

// ##### writeFile() #################################################
void XpmWriter::writeFile(IndexOct* tree) throw (WriteFileException*) {
  assert (DIMENSIONS == 3);
  assert (tree != NULL);

  octree= tree;

  for (sectAxis= 0; sectAxis < DIMENSIONS; ++sectAxis) {
    cout << "Schnitt entlang der " << (char)(sectAxis + 'x') << "-Achse" 
         << endl;

    int i[2];

    for (int h= 0; h < getWidth(); ++h) {
      out.open(getFileName(h));
      writeHeader(h);
      for (i[1]= 0; i[1] < getWidth(); ++i[1]) {
	writeLineBegin();
	for (i[0]= 0; i[0] < getWidth(); ++i[0]) {
	  write(getColorChar(h, i));
	}
	writeLineEnd((i[1]+1) == getWidth());
      }
      writeFooter();
      out.flush();
      out.close();
      cout << "Fortschritt " << (100*h)/(getWidth()-1) << "%" << char(13);
    }
  }
}

// EOF: src/writer/xpm_writer.cpp

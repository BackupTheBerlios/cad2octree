#include <fstream>

#define DEGREE 3
#define OFS 50

void curvePoint(double u, double bp[], double &x) {
  double p[DEGREE+1];
  for (int i= 0; i <= DEGREE; ++i) {
    p[i]= bp[i];
  }

  for (int i= 0; i < DEGREE; ++i) {
    for (int k= i+1; k <= DEGREE; ++k) {
      p[k-i-1]= (1-u)*p[k-i-1] + u*p[k-i];
    }
  }
  x= p[0];
}

int getWidth(double p[]) {
  int min= (int)p[0];
  int max= min;
  for (int k= 1; k <= DEGREE; ++k) {
    if (min > (int)p[k]) {
      min= (int)p[k];
    }
    if (max < (int)p[k]) {
      max= (int)p[k];
    }
  }
  return max - min + 100;
}

char getXDir(int k, int i) {
  if (k <= 1) {
    return 'r';
  } else if (i-k > 1) {
    return 'l';
  } 
  return 'c';
}

char getYDir(int k, int i) {
  if (i == 1 && k % 2 == 1) {
    return 'c';
  }
  if (i == 0 || i == 3) {
    if (i == k || i-k == 3) {
      return 't';
    }
  }
  return 'b';
}

void writeBezier(ofstream &out, unsigned step, double px[], double py[]) {
  out << "%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Bezier-Kurve %%" << endl;
  out << "%%%%%%%%%%%%%%%%%%" << endl;
  out << "\\drawline";
  for (unsigned i= 0; i <= step; ++i) {
    double x;
    double y;
    curvePoint(double(i)/double(step), px, x);
    curvePoint(double(i)/double(step), py, y);
    out << "(" << OFS+(int)x << "," << OFS+(int)y << ")";
    if ((i % 5) == 4) {
      out << endl << "\t";
    }
  }
  out << endl;
}

void writeBP(ofstream &out, double u, double px[], double py[]) {
  double p[DEGREE+1][2];
  for (int i= 0; i <= DEGREE; ++i) {
    p[i][0]= px[i];
    p[i][1]= py[i];
  }

  out << "%%%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Kontrollpunkte %%" << endl;
  out << "%%%%%%%%%%%%%%%%%%%%" << endl;
  for (int i= 0; i<= DEGREE; ++i) {
    for (int k= i; k<= DEGREE; ++k) {
      out << "\\put(" << OFS+(int)p[k-i][0] << "," << OFS+(int)p[k-i][1];
      out << "){";
      if (i == DEGREE) {
	out << "\\color{white}\\circle*{20}}" << endl;
	out << "\t\\put(" << OFS+(int)p[k-i][0] << "," << OFS+(int)p[k-i][1];
        out << "){\\normalcolor\\circle" << endl;
      } else {
        out << "\\circle*";
      }
      out << "{20}}" << endl;
      out << "\t\\put(" << OFS+(int)p[k-i][0] << "," << OFS+(int)p[k-i][1];
      out << "){\\makebox(0,0)[" << getXDir(k, i) << getYDir(k, i);
      out << "]{${\\bf b}_" << k << "^" << i;
      out << "$}}" << endl;
      if (k>i) {
        p[k-i-1][0]= (1-u)*p[k-i-1][0] + u*p[k-i][0];
        p[k-i-1][1]= (1-u)*p[k-i-1][1] + u*p[k-i][1];
      }
    }
    out << endl;
  }
  out << endl;
}

void writeFooter(ofstream &out) {
  out << "\\end{picture}" /* << "}" */ << endl << endl;
}

void writeHeader(ofstream &out, double px[], double py[]) {
  out << "% doc/graf/castel.tex" << endl;
  out << "% Casteljau-Algorithmus, Geometrische Konstruktion" << endl;
  out << "% " << endl;
  out << "% Ausarbeitung zur Diplomarbeit Nr. 2035 - " << '"'
      << "Erzeugung und Evaluierung " << endl; 
  out << "% von Oktalbaumstrukturen als Schnittstelle zu CAD-Programmen" 
      << '"' << endl;
  out << "%" << endl;
  out << "% Autor: Stefan Mahler 2002" << endl;
  out << "%   Universitaet Stuttgart, SgS" << endl;
  out << "% Betreuer: Ralf Mundani" << endl;
  out << endl;
  out << endl;
  out << "\\setlength{\\unitlength}{0.1mm}" << endl;
  int x= getWidth(px);
  int y= getWidth(py);
  out << "\\begin{picture}(" << x << "," << y << ")" << endl << endl;
}

void writeLines(ofstream &out, double u, double px[], double py[]) {
  double p[DEGREE+1][2];
  for (int i= 0; i <= DEGREE; ++i) {
    p[i][0]= px[i];
    p[i][1]= py[i];
  }

  out << "%%%%%%%%%%%%%%%%%%" << endl;
  out << "%% Hilfslinien %%" << endl;
  out << "%%%%%%%%%%%%%%%%%%" << endl;
  for (int i= 0; i<= DEGREE; ++i) {
    out << "\\drawline";
    for (int k= i; k<= DEGREE; ++k) {
      out << "(" << OFS+(int)p[k-i][0] << "," << OFS+(int)p[k-i][1] << ")";
      if (k>i) {
        p[k-i-1][0]= (1-u)*p[k-i-1][0] + u*p[k-i][0];
        p[k-i-1][1]= (1-u)*p[k-i-1][1] + u*p[k-i][1];
      }
    }
    out << endl;
  }
  out << endl;
}


int main(int argc, const char *argv[]) {
  ofstream out;
  out.open("castel.tex");

  double px[DEGREE+1]= {20, 100, 900, 1100};
  double py[DEGREE+1]= {20, 500, 500, 200};
  double u= 2.0/3.0;
  int step= 500;

  writeHeader(out, px, py);
  writeBezier(out, step, px, py);
  writeLines(out, u, px, py);
  writeBP(out, u, px, py);
  writeFooter(out);

  if (out.is_open()) {
    out.close();
  }
    
  return 0;
}

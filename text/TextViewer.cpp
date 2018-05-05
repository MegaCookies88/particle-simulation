#include "TextViewer.hpp"
#include "GrainLJTUn.hpp"
#include "GrainLJTDeux.hpp"
#include "Systeme.hpp"
#include "Plan.hpp"
#include "Dalle.hpp"
#include "Sphere.hpp"
#include "Cylindre.hpp"
#include "Brique.hpp"
#include "Bac.hpp"
#include "Source.hpp"
#include <iostream>
using namespace std;

void TextViewer::dessine(GrainLJTUn const& o){
  cout << o;
}

void TextViewer::dessine(GrainLJTDeux const& o){
  cout << o;
}

void TextViewer::dessine(Systeme const& o){
  cout << o;
}

void TextViewer::dessine(Plan const& o){
  cout << o;
}

void TextViewer::dessine(Dalle const& o){
  cout << o;
}

void TextViewer::dessine(Sphere const& o){
  cout << o;
}

void TextViewer::dessine(Cylindre const& o){
  cout << o;
}

void TextViewer::dessine(Source const& s){
  cout << s;
}

void TextViewer::dessine(Brique const& b){
  cout << b;
}

void TextViewer::dessine(Bac const& b){
  cout << b;
}

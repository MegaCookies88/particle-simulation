#include "Cylindre.hpp"
#include "Vecteur3D.hpp"
#include "Obstacle.hpp"
#include "Plan.hpp"
#include <iostream>
#include <cmath>
using namespace std;

//unites : rayon et hauteur en mm
Cylindre::Cylindre(Vecteur3D const& position, Vecteur3D const& vitesse, double rayon, double hauteur,
   Vecteur3D const& normale,SupportADessin* sup)
  : Obstacle(position,vitesse,sup),
    rayon(rayon*1e-3),
    hauteur(hauteur*1e-3),
    normale(normale.normalise())
  {}

Vecteur3D Cylindre::PointPlusProche(Vecteur3D const& x_i) const{
  Vecteur3D e(x_i - position);
  Vecteur3D en((e*normale)*normale);

  if( fabs(e*normale) < (hauteur/2.0) ){
    return position + en + rayon*((e-en).normalise());
  }
  else{
    return position + (hauteur/2.0)*en.normalise() + fmin(rayon,(e-en).norme())*(e-en).normalise();
  }
}

ostream& Cylindre::affiche(ostream& sortie) const{
  sortie << "Cylindre d'origine (" << 1e3*position << "), de rayon (" << 1e3*rayon << "), de hauteur (";
  sortie << 1e3*hauteur << ") et de normale (" << normale << ")";
  return sortie;
}

void Cylindre::dessine(){
  if (support != nullptr) support->dessine(*this);
}

void Cylindre::rotate(double const& dt){
  Plan p(position,vitesse,normale,support);
  Vecteur3D tr(position - (p.PointDuPlan()).normalise());
  normale+= 10*dt*tr;
  normale.normalise();
}

void Cylindre::bouger(double const& dt){
  rotate(dt);
}

#include "Sphere.hpp"
#include <iostream>
#include <cmath>

using namespace std;

//unites : rayon en mm
Sphere::Sphere(Vecteur3D const& position, Vecteur3D const& vitesse, double rayon, SupportADessin* sup)
  : Obstacle(position,vitesse,sup),
    rayon(rayon*1e-3)
  {}

Vecteur3D Sphere::PointPlusProche(Vecteur3D const& x_i) const{
  return position + rayon*(x_i - position);
}

ostream& Sphere::affiche(ostream& sortie) const{
  sortie << "Sphere d'origine (" << 1e3*position << ") et de rayon (" << 1e3*rayon << ") ";
  return sortie;
}

void Sphere::dessine(){
  if (support != nullptr) support->dessine(*this);
}

void Sphere::bouger(double const& dt){
  translate(dt);
}

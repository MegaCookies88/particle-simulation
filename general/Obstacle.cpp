#include "Obstacle.hpp"
#include "GrainLJ.hpp"
#include <iostream>
using namespace std;

Obstacle::Obstacle(Vecteur3D const& position, Vecteur3D const& vitesse, SupportADessin* sup)
  : Objet(position,vitesse),
    Dessinable(sup)
  {}

ostream& Obstacle::affiche(ostream& sortie) const{
  sortie << "Obstacle d'origine (" << 1e3*position << ")";
  return sortie;
}

void Obstacle::translate(double const& dt){
  position+=10*dt*vitesse;
}

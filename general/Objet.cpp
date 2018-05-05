#include "Objet.hpp"
#include <cmath>

using namespace std;

//Les donnees sont introduites en mm et en mm/s
Objet::Objet(Vecteur3D const& p, Vecteur3D const& v)
  : position(p*1e-3),
    vitesse(v*1e-3)
  {}

Vecteur3D Objet::getPosition() const{
  return position;
}

void Objet::setPosition(Vecteur3D const& p){
  position = p;
}

double Objet::getVitesse() const{
  return vitesse.norme();
}

void Objet::setVitesse(Vecteur3D const& v){
  vitesse = v;
}

ostream& operator<<(ostream& sortie, Objet const& objet){
  objet.affiche(sortie);
  return sortie;
}

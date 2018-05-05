#include "Dalle.hpp"
#include <iostream>
using namespace std;

//unites : longueur et largeur en mm
Dalle::Dalle(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale,
  double longueur, double largeur, Vecteur3D const& direction, SupportADessin* sup)
  : Plan(position,vitesse,normale,sup),
    longueur(longueur*1e-3),
    largeur(largeur*1e-3),
    direction(direction.normalise())
  {}

Dalle::Dalle(Plan const& plan, double longueur, double largeur, Vecteur3D const& direction)
  : Plan(plan),
    longueur(longueur*1e-3),
    largeur(largeur*1e-3),
    direction(direction.normalise())
  {}

Vecteur3D Dalle::PointPlusProche(Vecteur3D const& x_i) const{
  Vecteur3D res(Plan::PointPlusProche(x_i));
  double x_lo((res-position)*direction);
  double x_la((res-position)*(normale^direction));
  if(x_lo > longueur){
    res-=(x_lo-longueur)*direction;
  }else{
    if(x_lo < 0){
      res-=x_lo*direction;
    }
  }
  if(x_la > largeur){
    res-=(x_la-largeur)*(normale^direction);
  }else{
    if(x_la < 0){
      res-=x_la*(normale^direction);
    }
  }
  return res;
}

void Dalle::rotate(double const& dt){
  Vecteur3D tr(-normale);
  normale+=30*dt*direction;
  direction+=30*dt*tr;
  normale=normale.normalise();
  direction=direction.normalise();
}

void Dalle::bouger(double const& dt){
    translate(dt);
    rotate(dt);
}

ostream& Dalle::affiche(ostream& sortie) const{
  if(longueur==largeur) {
    sortie << "Carre";
  }
  else{
    sortie << "Rectangle";
  }
  sortie << " d'origine (" << 1e3*position << ") et de normale (" << normale;
  sortie << ") longueur= "<< 1e3*longueur<<" , largeur= "<< 1e3*largeur << " ";
  return sortie;
}

void Dalle::dessine(){
  if (support != nullptr) support->dessine(*this);
}

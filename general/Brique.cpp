#include "Brique.hpp"
#include <iostream>
using namespace std;

Brique::Brique(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale,
    double longueur, double largeur, double hauteur, Vecteur3D const& direction, SupportADessin* sup)
    : Obstacle(position,vitesse,sup),
      faces({Dalle(position,vitesse,normale,longueur,largeur,direction,support),
             Dalle(position,vitesse,-(normale^direction),hauteur,longueur,-normale,support),
             Dalle(position,vitesse,-direction,largeur,hauteur,normale^direction,support),
             Dalle(position+longueur*direction,vitesse,direction,hauteur,largeur,-normale,support),
             Dalle(position+largeur*(normale^direction),vitesse,normale^direction,longueur,hauteur,direction,support),
             Dalle(position-hauteur*normale,vitesse,-normale,largeur,longueur,normale^direction,support)
           })
    {}

Vecteur3D Brique::PointPlusProche(Vecteur3D const& x_i) const{
  Vecteur3D res(faces[0].PointPlusProche(x_i));
  for(size_t i(1); i<faces.size(); i++){
      if((faces[i].PointPlusProche(x_i)-x_i).norme() < (res-x_i).norme()) res=faces[i].PointPlusProche(x_i);
  }
  return res;
}

ostream& Brique::affiche(ostream& sortie) const{
  sortie << "Brique d'origine (" << 1e3*position << ")";
  return sortie;
}

void Brique::dessine(){
  if (support != nullptr) support->dessine(*this);
}

void Brique::bouger(double const& dt){
  (void)dt;
}

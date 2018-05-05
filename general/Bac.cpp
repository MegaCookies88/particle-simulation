#include "Bac.hpp"
#include <iostream>
using namespace std;

Vecteur3D Bac::normale = Vecteur3D(0,0,1);

Bac::Bac(Vecteur3D const& position, Vecteur3D const& vitesse,
    double longueur, double largeur, double hauteur, Vecteur3D const& direction, SupportADessin* sup)
    : Obstacle(position,vitesse,sup),
      faces({Dalle(position-hauteur*normale,vitesse,-normale,largeur,longueur,normale^direction,support),
             Dalle(position,vitesse,-(normale^direction),hauteur,longueur,-normale,support),
             Dalle(position,vitesse,-direction,largeur,hauteur,normale^direction,support),
             Dalle(position+longueur*direction,vitesse,direction,hauteur,largeur,-normale,support),
             Dalle(position+largeur*(normale^direction),vitesse,normale^direction,longueur,hauteur,direction,support)
           })
    {}

Vecteur3D Bac::PointPlusProche(Vecteur3D const& x_i) const{
  Vecteur3D res(faces[0].PointPlusProche(x_i));
  for(size_t i(1); i<faces.size(); i++){
      if((faces[i].PointPlusProche(x_i)-x_i).norme() < (res-x_i).norme()) res=faces[i].PointPlusProche(x_i);
  }
  return res;
}

ostream& Bac::affiche(ostream& sortie) const{
  sortie << "Bac a eau d'origine (" << 1e3*position << ")";
  return sortie;
}

void Bac::dessine(){
  if (support != nullptr) support->dessine(*this);
}

void Bac::bouger(double const& dt){
  (void)dt;
  //On ne bouge pas le bac.
}

bool Bac::grain_dans_bac(Vecteur3D const& x_i) const{
  if( (faces[1].PointPlusProche(x_i)-x_i).norme()+(faces[4].PointPlusProche(x_i)-x_i).norme() == faces[0].longueur
    && (faces[2].PointPlusProche(x_i)-x_i).norme()+(faces[3].PointPlusProche(x_i)-x_i).norme() == faces[0].largeur
    && x_i.getZ()>position.getZ()-faces[1].longueur && x_i.getZ()<0.7*faces[1].longueur) return true;
    return false;
}

void Bac::changer_univers(unique_ptr<GrainLJ>& g) const{
  if(grain_dans_bac(g->getPosition())){
      g->changer_milieu("eau");
    }else{
      g->changer_milieu("air");
    }
}

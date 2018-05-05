#include "Plan.hpp"
#include <iostream>
using namespace std;

Plan::Plan(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale,SupportADessin* sup, bool invisible)
  : Obstacle(position,vitesse,sup),
    normale(normale.normalise()),
    invisible(invisible)
  {}

Vecteur3D Plan::PointPlusProche(Vecteur3D const& x_i) const{
  return x_i + ((position-x_i)*normale)*normale;
}

Vecteur3D Plan::PointDuPlan() const{
  double a(normale.getX()), b(normale.getY()), c(normale.getZ());
  double x_0(position.getX()), y_0(position.getY()), z_0(position.getZ());
  double alpha(a*x_0+b*y_0+c*y_0);

  if(c!=0){
      return Vecteur3D(x_0+1, y_0+1, (alpha - a*(x_0+1) - b*(y_0+1))/c);
   }else{
     if(b!=0){
       return Vecteur3D(x_0+1, (alpha - a*(x_0+1) - c*(z_0+1))/b, z_0+1);
     }else{
        return Vecteur3D((alpha - b*(y_0+1) - c*(z_0+1))/a, y_0+1, z_0+1);
     }
   }
}

void Plan::bouger(double const& dt){
    translate(dt);
}

ostream& Plan::affiche(ostream& sortie) const{
  sortie << "Plan d'origine (" << 1e3*position << ") et de normale (" << normale << ") ";
  return sortie;
}

void Plan::dessine(){
  if (support != nullptr) support->dessine(*this);
}

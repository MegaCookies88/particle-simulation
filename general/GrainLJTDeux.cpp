#include "GrainLJTDeux.hpp"
#include <cmath>
using namespace std;

GrainLJTDeux::GrainLJTDeux(Grain const& g, SupportADessin* const& sup) : GrainLJ(g,sup) {}

void GrainLJTDeux::dessine(){
  if (support != nullptr) support->dessine(*this);
}

std::ostream& GrainLJTDeux::affiche(std::ostream& sortie) const{
  sortie << "Grain L-J de type 2 : " << "[ pos= ("<<1e3*position<<"), v= ("<<1e3*vitesse<<"), m= ";
  sortie <<1e6*masse()<<", r= "<<1e3*rayon<<" ]";
  return sortie;
}

#include "GrainLJTUn.hpp"
#include <cmath>
using namespace std;

GrainLJTUn::GrainLJTUn(Grain const& g, SupportADessin* sup) : GrainLJ(g,sup) {}

void GrainLJTUn::dessine(){
  if (support != nullptr) support->dessine(*this);
}

std::ostream& GrainLJTUn::affiche(std::ostream& sortie) const{
  sortie << "Grain L-J de type 1 : " << "[ pos= ("<<1e3*position<<"), v= ("<<1e3*vitesse<<"), m= ";
  sortie <<1e6*masse()<<", r= "<<1e3*rayon<<" ]";
  return sortie;
}

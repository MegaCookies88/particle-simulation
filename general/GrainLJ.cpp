#include "GrainLJ.hpp"
#include <cmath>
#include <memory>
using namespace std;

double GrainLJ::epsilon = 25e-15; //kg.m3 / s2
double GrainLJ::sigma = 0.885e-3; // m

GrainLJ::GrainLJ(Grain const& g, SupportADessin* const& sup)
  : Grain(g),
    Dessinable(sup)
  {}

//forceLJ retourne directement la norme de la force totale
double GrainLJ::forceLJ(double const& x){
  double res((24*epsilon)/(sigma*sigma));
  if(x >= 2 || x == 0) return 0;
  if(x <= 1) return -res;
  return res*((pow(x,6)-2.0)/(pow(x,13)));
}

//centre du grain1 au grain2
void GrainLJ::ajouteForce(unique_ptr<GrainLJ> const& g){

  //deplacer le grain si il est trop proche du deuxieme
  if((g->position-position).norme() <= rayon+g->rayon){
    Vecteur3D u((g->position-position).normalise());
    position=g->position-(rayon+g->rayon)*u;
    vitesse-=(vitesse*u)*u;
  }

  double mult(forceLJ(1.09 + ((position - g->position).norme()-rayon-g->rayon)/sigma));

  //force pour deplacer normalement le grain
  if(mult != 0) force+= mult*((g->position-position).normalise());
}

//centre du grain au point le plus proche de l’obstacle
void GrainLJ::ajouteForce(unique_ptr<Obstacle> const& o){

  //deplacer le grain si il est trop proche de l'obstacle
  if((o->PointPlusProche(position)-position).norme() <= rayon){
    Vecteur3D u((o->PointPlusProche(position)-position).normalise());
    position=o->PointPlusProche(position)-(rayon)*u;
    vitesse-=(vitesse*u)*u;
  }

  double mult(forceLJ(1.09 + ((position - o->PointPlusProche(position)).norme()-rayon)/sigma));

  //force pour deplacer normalement le grain
  if(mult != 0) force+= 2*mult*((o->PointPlusProche(position)-position).normalise());
}

void GrainLJ::ajouteForce(Vecteur3D const& f){
  force+=f;
}

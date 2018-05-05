#include "Grain.hpp"
#include "Univers.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace univers;

// unites : distances en mm / vitesse en mm/s / massevolumique en mg/mm3
Grain::Grain(Vecteur3D const& position, Vecteur3D const& vitesse, double mv, double rayon)
  : Objet(position,vitesse),
    massevolumique(mv*1e3),
    rayon(rayon*1e-3),
    force(Vecteur3D())
  {}

double Grain::getRayon() const{
  return rayon;
}

void Grain::setRayon(double const& r){
  rayon = r;
}

Vecteur3D Grain::getForce() const{
  return force;
}

//affichage en mm / mg / s
ostream& Grain::affiche(ostream& sortie) const{
  sortie << "P= " << 1e3*position << "| V= " << 1e3*vitesse << "| M= ";
  sortie << 1e6*masse() << "| R= " << 1e3*rayon;
  return sortie;
}

double Grain::masse() const{
  return massevolumique*(4.0/3.0)*M_PI*pow(rayon,3);
}

double Grain::lambda() const{
  if(vitesse.norme() <= milieu.comp_milieu/rayon){
    return 6.0*M_PI*rayon*milieu.visc_milieu;
  }
  else{
    return (9.0*M_PI*rayon*rayon*milieu.m_vol_milieu*vitesse.norme()/40.0);
  }
}

void Grain::changer_milieu(string const& nom){
    milieu = Milieu(nom);
}

void Grain::ajouteForce(){
  force+=Vecteur3D(0,0,milieu.m_vol_milieu*gravite*(4.0/3.0)*M_PI*pow(rayon,3)-masse()*gravite);
  force-=lambda()*vitesse;
}

void Grain::bouger(double const& dt){
  vitesse+=(dt/masse())*force;
  position+=dt*vitesse;
  force=Vecteur3D();
}

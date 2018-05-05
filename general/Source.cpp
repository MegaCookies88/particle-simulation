#include "Source.hpp"
#include "GrainLJTUn.hpp"
#include "GrainLJTDeux.hpp"
#include "Aleatoire.hpp"
#include <vector>
#include <cmath>
#include <memory>
using namespace std;

double Source::rayon_arc = 0.7e-2;

//ecart type doit etre de meme ordre de grandeur que le rayon des grains
Source::Source(Grain* const& g_ini, Vecteur3D const& position, Vecteur3D const& vitesse,
  double ec_vitesse, double ec_rayon, unsigned int debit, SupportADessin* sup, bool e)
  : Objet(position, Vecteur3D()),
    Dessinable(sup),
    g_ini(g_ini),
    vitesse_ini(vitesse*1e-3),
    ec_vitesse(ec_vitesse*1e-3),
    ec_rayon(ec_rayon*1e-3),
    debit(debit),
    etat(e)
  {}

void Source::on(){
  etat = true;
}
void Source::off(){
  etat = false;
}

void Source::creation(vector<unique_ptr<GrainLJ>>& tab, double const& dt) const{
//si la source est en marche
if(etat == true){

//nombre de grains a ajouter
  Aleatoire generateur;
  double fraction(debit*dt);
  int nombre(fraction);
  fraction -= nombre;
  if ( generateur.uniforme(0.0, 1.0) < fraction ) ++nombre;

//ajout des grains
  for(int i(0);i<nombre;i++){
    Grain grain(*g_ini);

    grain.setPosition(Vecteur3D(generateur.uniforme(position.getX()-rayon_arc,position.getX()+rayon_arc),
                                position.getY(),
                                position.getZ()
                                ));

    grain.setVitesse(Vecteur3D(generateur.gaussienne(vitesse_ini.getX(),ec_vitesse),
                               generateur.gaussienne(vitesse_ini.getY(),ec_vitesse),
                               generateur.gaussienne(vitesse_ini.getZ(),ec_vitesse)
                               ));

//empecher d'avoir un rayon negatif
    double r(0);
    do{
      r = generateur.gaussienne(grain.getRayon(),ec_rayon);
    }while(r <= 0);
    grain.setRayon(r);

//bouger le grain directement d un dt
    grain.ajouteForce();
    grain.bouger(0.003);

//random 0 ou 1 pour choisir le type du grainLJ
    if(rand()%2 == 0){
      tab.push_back(unique_ptr<GrainLJ>(new GrainLJTUn(grain,support)));
    }else{
      tab.push_back(unique_ptr<GrainLJ>(new GrainLJTDeux(grain,support)));
    }
  }
}
}

void Source::changer_support(SupportADessin* const& sup){
   support=sup;
}

std::ostream& Source::affiche(std::ostream& sortie) const{
  sortie << "Source : [ pos = ("<<1e3*position<<"), etat = "<<etat<<" , debit = "<<debit<<" ]";
  return sortie;
}

void Source::dessine(){
  if (support != nullptr) support->dessine(*this);
}

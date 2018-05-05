#include "Systeme.hpp"
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

double Systeme::distance_max = 0.11;

bool Systeme::obstacle_mvt = false;

Systeme::Systeme(SupportADessin* const& sup)
  : Dessinable(sup),
    liste_sources(vector<unique_ptr<Source>>(0)),
    liste_grains(vector<unique_ptr<GrainLJ>>(0)),
    liste_obstacles(vector<unique_ptr<Obstacle>>(0))
  {}

void Systeme::vider(){
  liste_sources.clear();
  liste_grains.clear();
  liste_obstacles.clear();
}

void Systeme::verifie_systeme(){
  for(size_t i(0);i<liste_grains.size();i++){
    //si le grain est trop loin on l'efface
    if(liste_grains[i]->position.norme() > distance_max) liste_grains.erase(liste_grains.begin()+i);
    for(size_t j(0);j<liste_obstacles.size();j++){
      //si l obstacle est trop loin on l'efface
      if(liste_obstacles[j]->position.norme() > distance_max) liste_obstacles.erase(liste_obstacles.begin()+j);
      //obstacle modifie ce qui l'entoure
      liste_obstacles[j]->changer_univers(liste_grains[i]);
    }
  }
}

//adapt_dt n'est pas tres juste du point de vue physique car chaque grain peut bouger avec un dt different
//mais du point de vue graphique et calcul il est mieux de faire comme ci dessous
double Systeme::adapt_dt(double const& dt, unique_ptr<GrainLJ> const& grain) const{
  double vitesse((grain->vitesse).norme());
  double dt2(grain->getRayon()/(2.0*vitesse));
  return fmin(dt,dt2);
}

void Systeme::evolue(double const& dt){
  for(auto& src : liste_sources){
    src->creation(liste_grains,0.1);
  }

  for(auto& gr1 : liste_grains){
    gr1->Grain::ajouteForce();
    for(auto& ob : liste_obstacles){
      gr1->ajouteForce(ob);
    } //la force qu'exerce l'obstacle sur le grain
    for(auto& gr2 : liste_grains){
      gr1->ajouteForce(gr2);
    } //la force qu'exerce d'autres grains sur un grain
    gr1->bouger(adapt_dt(dt,gr1));
  }

  if(obstacle_mvt){
      for(auto& ob : liste_obstacles){
          ob->bouger(dt);
      }
  }
  verifie_systeme();
}

void Systeme::ajouter_Grain(GrainLJ* g){
  if(g != nullptr){
    g->changer_support(support);
    liste_grains.push_back(unique_ptr<GrainLJ>(g));
  }
}

void Systeme::ajouter_Obstacle(Obstacle* o){
  if(o != nullptr){
    o->changer_support(support);
    liste_obstacles.push_back(unique_ptr<Obstacle>(o));
  }
}

void Systeme::ajouter_Source(Source* s){
  if(s != nullptr){
    s->changer_support(support);
    liste_sources.push_back(unique_ptr<Source>(s));
  }
}

void Systeme::stop_start_sources(){
    for(auto& src : liste_sources){
        src->etat = !src->etat;
    }
}

void Systeme::stop_start_obstacles(){
    Systeme::obstacle_mvt = !Systeme::obstacle_mvt;
}

ostream& Systeme::affiche(ostream& sortie) const{
  if(liste_sources.size()!=0){
    sortie << "Le système possède les "<<liste_sources.size()<<" sources suivantes :"<<endl;
    for(size_t i(0);i<liste_sources.size();i++){
      sortie << *liste_sources[i] << endl;
    }
  }
  if(liste_grains.size()!=0){
    sortie << "Le système est constitué des "<<liste_grains.size()<<" grains suivants :"<<endl;
    for(size_t i(0);i<liste_grains.size();i++){
      sortie << *liste_grains[i] << endl;
    }
  }
  if(liste_obstacles.size()!=0){
    sortie << "et les "<<liste_obstacles.size()<<" obstacles suivants :"<<endl;
    for(size_t i(0);i<liste_obstacles.size();i++){
      sortie << *liste_obstacles[i] << endl;
    }
  }
  return sortie;
}

ostream& operator<<(ostream& sortie, Systeme const& s){
  s.affiche(sortie);
  return sortie;
}

void Systeme::dessine(){
  if (support != nullptr) support->dessine(*this);
}

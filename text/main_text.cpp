#include <iostream>
#include <cmath>
#include "Systeme.hpp"
#include "Objet.hpp"
#include "Grain.hpp"
#include "GrainLJTUn.hpp"
#include "GrainLJTDeux.hpp"
#include "Obstacle.hpp"
#include "Plan.hpp"
#include "TextViewer.hpp"
using namespace std;

int main() {

  TextViewer* support = new TextViewer();
  Systeme systeme(support);

//RAPPEL: unites en mm / mg

  systeme.ajouter_Grain(
    new GrainLJTUn(Grain(Vecteur3D(),Vecteur3D(),1.0,0.4), support)
              );
  systeme.ajouter_Grain(
    new GrainLJTUn(Grain(Vecteur3D(1,0,0),Vecteur3D(),1.0,0.4), support)
              );
  systeme.ajouter_Grain(
    new GrainLJTUn(Grain(Vecteur3D(0.5,sqrt(3)/2.0,0),Vecteur3D(),1.0,0.4), support)
              );
  systeme.ajouter_Grain(
    new GrainLJTDeux(Grain(Vecteur3D(0.5,sqrt(3)/6.0,sqrt(6)/3.0),Vecteur3D(),1.0,0.4), support)
              );

  systeme.ajouter_Obstacle(new Plan(Vecteur3D(0,0,-0.9),Vecteur3D(),Vecteur3D(0,0,1), support)
              );

  double dt(0.001);
  double t(0);
  do{
    cout << "Temps " << t << " :" << endl;
    systeme.dessine();
    systeme.evolue(dt);
    t+=dt;
  }while(t<=0.101);

  delete support;

  return 0;
}

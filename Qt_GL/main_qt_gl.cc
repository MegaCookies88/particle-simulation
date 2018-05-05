#include <QApplication>
#include <QtWidgets>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  VueOpenGL vue;

  GLWidget w;
  //appuyer sur N ou M pour switcher de fenetre
  //simulation generale
  //bac a eau (changement du milieu)
  //planche de Galton

  //-------------------------------------------------------------------------------------------------------

  w.systeme[0]->ajouter_Obstacle(new Plan(Vecteur3D(),Vecteur3D(),Vecteur3D(0,0,1),&vue));

  w.systeme[0]->ajouter_Obstacle(new Sphere(Vecteur3D(-15,30,8), Vecteur3D(-10,-20,7),8,&vue));
  w.systeme[0]->ajouter_Obstacle(new Sphere(Vecteur3D(60,-20,20), Vecteur3D(0,-20,0),15,&vue));

  w.systeme[0]->ajouter_Obstacle(new Bac(Vecteur3D(0,-80,6),Vecteur3D(),60,40,5,Vecteur3D(1,0,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Cylindre(Vecteur3D(35,40,20),Vecteur3D(5.7,9,4),4,40,Vecteur3D(0,0,1),&vue));

  w.systeme[0]->ajouter_Obstacle(new Cylindre(Vecteur3D(-50,40,20),Vecteur3D(5.7,9,4),4,40,Vecteur3D(0,0,1),&vue));
  w.systeme[0]->ajouter_Obstacle(new Cylindre(Vecteur3D(-40,40,20),Vecteur3D(5.7,9,4),4,40,Vecteur3D(0,0,1),&vue));
  w.systeme[0]->ajouter_Obstacle(new Cylindre(Vecteur3D(-50,60,20),Vecteur3D(5.7,9,4),4,40,Vecteur3D(0,0,1),&vue));
  w.systeme[0]->ajouter_Obstacle(new Cylindre(Vecteur3D(-40,60,20),Vecteur3D(5.7,9,4),4,40,Vecteur3D(0,0,1),&vue));

  w.systeme[0]->ajouter_Obstacle(new Brique(Vecteur3D(-30,40,60),Vecteur3D(-200,0,0),Vecteur3D(0,0,1),20,30,20,Vecteur3D(0,1,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Dalle(Vecteur3D(-10,-10,0),Vecteur3D(),Vecteur3D(0,0,1),20,20,Vecteur3D(1,0,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Dalle(Vecteur3D(-10,10,0),Vecteur3D(),Vecteur3D(0,-1,-0.5),20,15,Vecteur3D(1,0,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Dalle(Vecteur3D(10,-10,0),Vecteur3D(),Vecteur3D(0,1,-0.5),20,15,Vecteur3D(-1,0,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Dalle(Vecteur3D(-10,1,12),Vecteur3D(),Vecteur3D(0,-1,0.5),20,15,Vecteur3D(1,0,0),&vue));

  w.systeme[0]->ajouter_Obstacle(new Dalle(Vecteur3D(-10,-1,12),Vecteur3D(),Vecteur3D(0,-1,-0.5),20,15,Vecteur3D(1,0,0),&vue));

  w.systeme[0]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.4),
                               Vecteur3D(15,-65,30),Vecteur3D(0,0,0),0.1,0.1,10.0,&vue,false));

  w.systeme[0]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.4),
                               Vecteur3D(35,40,50),Vecteur3D(0,0,0),0.1,0.1,10.0,&vue,false));

  w.systeme[0]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.4),
                               Vecteur3D(-45,50,70),Vecteur3D(0,0,0),0.1,0.1,10.0,&vue,false));

  w.systeme[0]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.4),
                               Vecteur3D(0,0,25),Vecteur3D(0,0,0),0.1,0.1,10.0,&vue,false));

  //-------------------------------------------------------------------------------------------------------

  w.systeme[1]->ajouter_Obstacle(new Bac(Vecteur3D(0,0,20),Vecteur3D(),30,20,20,Vecteur3D(1,0,0),&vue));

  w.systeme[1]->ajouter_Obstacle(new Plan(Vecteur3D(),Vecteur3D(),Vecteur3D(0,0,1),&vue));

  //grains legers et grands donc flottent
  w.systeme[1]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,1),
                               Vecteur3D(15,10,30),Vecteur3D(0,0,0),0,0,2,&vue,false));

  //grains lourds et petits donc descendent au fond
  w.systeme[1]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),5,0.5),
                               Vecteur3D(15,10,30),Vecteur3D(0,0,0),0,0,2,&vue,false));

  //grains a l'exterieur du bac descendent normalement
  w.systeme[1]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(0,0,0),1.0,0.5),
                               Vecteur3D(-15,10,30),Vecteur3D(0,0,0),0.2,0.2,4,&vue,false));

  //-------------------------------------------------------------------------------------------------------

  w.systeme[2]->ajouter_Obstacle(new Plan(Vecteur3D(),Vecteur3D(),Vecteur3D(0,0,1),&vue,true));

  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(-34.5,-2.5,0),Vecteur3D(),Vecteur3D(0,0,1),69,5,Vecteur3D(1.3,0,0),&vue));

  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(-34.5,2.5,0),Vecteur3D(),Vecteur3D(-1,0,0),5,100,Vecteur3D(0,-1,0),&vue));
  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(34.5,2.5,0),Vecteur3D(),Vecteur3D(-1,0,0),5,100,Vecteur3D(0,-1,0),&vue));

  w.systeme[2]->ajouter_Obstacle(new Plan(Vecteur3D(0,2.5,0),Vecteur3D(),Vecteur3D(0,1,0),&vue,true));
  w.systeme[2]->ajouter_Obstacle(new Plan(Vecteur3D(0,-2.5,0),Vecteur3D(),Vecteur3D(0,1,0),&vue,true));

  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(-1.5,2.5,65),Vecteur3D(),Vecteur3D(1,0,0),10,5,Vecteur3D(0,0,1),&vue));
  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(1.5,2.5,65),Vecteur3D(),Vecteur3D(1,0,0),10,5,Vecteur3D(0,0,1),&vue));

  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(-1.5,2.5,75),Vecteur3D(),Vecteur3D(1,0,3),35,5,Vecteur3D(-3,0,1),&vue));
  w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(1.5,-2.5,75),Vecteur3D(),Vecteur3D(-1,0,3),35,5,Vecteur3D(3,0,1),&vue));

  w.systeme[2]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.5),
                               Vecteur3D(25,0,95),Vecteur3D(0,0,100),2,0,20,&vue,false));
  w.systeme[2]->ajouter_Source(new Source(
                               new Grain(Vecteur3D(),Vecteur3D(),1.0,0.5),
                               Vecteur3D(-25,0,95),Vecteur3D(0,0,100),2,0,20,&vue,false));

  for(int j(-18); j<=18; j+=6){
      w.systeme[2]->ajouter_Obstacle(new Cylindre(Vecteur3D(j,0,57),Vecteur3D(),1.5,5,Vecteur3D(0,1,0),&vue));
  }
  for(int j(-27); j<=27; j+=6){
      w.systeme[2]->ajouter_Obstacle(new Cylindre(Vecteur3D(j,0,54),Vecteur3D(),1.5,5,Vecteur3D(0,1,0),&vue));
  }

  double nb(0);
  bool b(true);
  for(int i(51); i>=30; i-=3){
      if(b){
          nb=-30;
      }else{
          nb=-33;
      }
      b=!b;
      for(int j(nb); j<=-nb; j+=6){
          w.systeme[2]->ajouter_Obstacle(new Cylindre(Vecteur3D(j,0,i),Vecteur3D(),1.5,5,Vecteur3D(0,1,0),&vue));
      }
  }

  for(int j(-33); j<=33; j+=6){
      w.systeme[2]->ajouter_Obstacle(new Dalle(Vecteur3D(j,2.5,0),Vecteur3D(),Vecteur3D(-1,0,0),5,30,Vecteur3D(0,-1,0),&vue));
  }

  //-------------------------------------------------------------------------------------------------------

  w.show();

  return a.exec();
}

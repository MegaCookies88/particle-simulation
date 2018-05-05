#ifndef Obstacle_hpp
#define Obstacle_hpp

#include "Objet.hpp"
#include "Vecteur3D.hpp"
#include "Dessinable.hpp"
#include "SupportADessin.hpp"
class GrainLJ;
#include <memory>
#include <iostream>

class Obstacle : public Objet, public Dessinable{
public:

  Obstacle(Vecteur3D const& position, Vecteur3D const& vitesse, SupportADessin* sup);

  virtual std::ostream& affiche(std::ostream& sortie) const override;

  virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const = 0;

  void translate(double const& dt);

  virtual void rotate(double const& dt) {
    (void)dt;
  }

  virtual void bouger(double const& dt) = 0;

  virtual void changer_univers(std::unique_ptr<GrainLJ>& g) const {
    (void)g;
  }
  // ne fait rien pour la majorite des obstacles mais pour pouvoir utiliser cette methode
  // dans la classe systeme (par polymorphisme)
  // il faut l ajouter a tous les obstacles

};

#endif

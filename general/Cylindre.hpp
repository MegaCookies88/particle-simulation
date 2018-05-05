#ifndef Cylindre_hpp
#define Cylindre_hpp

#include "Obstacle.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"
#include <iostream>

class Cylindre : public Obstacle{
private:

  double rayon; // m
  double hauteur; //m
  Vecteur3D normale;

public:

  Cylindre(Vecteur3D const& position, Vecteur3D const& vitesse, double rayon, double hauteur,
           Vecteur3D const& normale, SupportADessin* sup);

  friend class VueOpenGL;

  Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

  std::ostream& affiche(std::ostream& sortie) const override;

  void dessine() override;

  void rotate(double const& dt) override;

  void bouger(double const& dt) override;

};

#endif

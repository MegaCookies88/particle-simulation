#ifndef Sphere_hpp
#define Sphere_hpp

#include "Obstacle.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"
#include <iostream>

class Sphere : public Obstacle{
private:

  double rayon; // m

public:

  Sphere(Vecteur3D const& position, Vecteur3D const& vitesse, double rayon, SupportADessin* sup);

  friend class VueOpenGL;

  Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

  std::ostream& affiche(std::ostream& sortie) const override;

  void dessine() override;

  void bouger(double const& dt) override;

};

#endif

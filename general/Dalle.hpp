#ifndef Dalle_hpp
#define Dalle_hpp

#include "Plan.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"

class Dalle : public Plan{
private:

  double longueur; // m
  double largeur; // m
  Vecteur3D direction; //direction longueur (orthogonale a la normale n)

public:

  Dalle(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale,
    double longueur, double largeur, Vecteur3D const& direction, SupportADessin* sup);

  Dalle(Plan const& plan, double longueur, double largeur,Vecteur3D const& direction);

  friend class VueOpenGL;
  friend class Bac;

  Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

  void rotate(double const& dt) override;

  void bouger(double const& dt) override;

  std::ostream& affiche(std::ostream& sortie) const override;

  void dessine() override;

};

#endif

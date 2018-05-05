#ifndef Grain_hpp
#define Grain_hpp

#include "Vecteur3D.hpp"
#include "Objet.hpp"
#include "Milieu.hpp"
#include <iostream>
#include <string>

class Grain : public Objet{
protected:

  double massevolumique; //en Kg/m3
  double rayon; //en m3
  Vecteur3D force;

  Milieu milieu = Milieu("air");

public:

  Grain(Vecteur3D const& position, Vecteur3D const& vitesse, double mv, double rayon);

  virtual ~Grain() {}

  double getRayon() const;
  void setRayon(double const& r);

  Vecteur3D getForce()const;

  std::ostream& affiche(std::ostream& sortie) const override;

  double masse() const; //en Kg

  double lambda() const;

  void changer_milieu(std::string const& nom);

  void ajouteForce();

  void bouger(double const& dt);

};

#endif

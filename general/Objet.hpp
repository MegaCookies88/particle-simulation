#ifndef Objet_hpp
#define Objet_hpp

#include "Vecteur3D.hpp"

class Objet{
protected:

  Vecteur3D position; // m
  Vecteur3D vitesse;  // m/s

public:

  Objet(Vecteur3D const& p, Vecteur3D const& v);

  friend class Systeme;

  Vecteur3D getPosition() const;
  void setPosition(Vecteur3D const& p);

  double getVitesse() const;
  void setVitesse(Vecteur3D const& v);

  virtual std::ostream& affiche(std::ostream& sortie) const = 0;


};

std::ostream& operator<<(std::ostream& sortie, Objet const& objet);

#endif

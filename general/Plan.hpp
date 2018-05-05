#ifndef Plan_hpp
#define Plan_hpp

#include "Obstacle.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"
#include "GrainLJ.hpp"
#include <memory>
#include <iostream>

class Plan : public Obstacle{
protected:

  Vecteur3D normale;
  bool invisible;

public:

  Plan(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale, SupportADessin* sup, bool invisible = false);

  friend class VueOpenGL;

  virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

  Vecteur3D PointDuPlan() const;

  virtual void bouger(double const& dt) override;

  std::ostream& affiche(std::ostream& sortie) const override;

  virtual void dessine() override;

};

#endif

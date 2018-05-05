#ifndef GrainLJ_hpp
#define GrainLJ_hpp

#include "Grain.hpp"
#include "Obstacle.hpp"
#include "Dessinable.hpp"
#include "SupportADessin.hpp"
#include <memory>

class GrainLJ : public Grain, public Dessinable{
protected:

  static double epsilon; // m3.Kg
  static double sigma; // m

public:

  GrainLJ(Grain const& g, SupportADessin* const& sup);

  virtual ~GrainLJ() {}

  static double forceLJ(double const& x);

  void ajouteForce(std::unique_ptr<GrainLJ> const& g);

  void ajouteForce(std::unique_ptr<Obstacle> const& o);

  void ajouteForce(Vecteur3D const& f);

};

#endif

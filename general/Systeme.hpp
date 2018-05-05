#ifndef Systeme_hpp
#define Systeme_hpp

#include <memory>
#include <vector>
#include <iostream>
#include "Objet.hpp"
#include "Grain.hpp"
#include "GrainLJ.hpp"
#include "Obstacle.hpp"
#include "Source.hpp"
#include "Dessinable.hpp"
#include "SupportADessin.hpp"

class Systeme : public Dessinable{
private:

  std::vector<std::unique_ptr<Source>> liste_sources;
  std::vector<std::unique_ptr<GrainLJ>> liste_grains;
  std::vector<std::unique_ptr<Obstacle>> liste_obstacles;

  static double distance_max; // m
  static bool obstacle_mvt; //bouger ou pas les obstacles

  Systeme(const Systeme&) = delete;

  Systeme& operator=(const Systeme&) = delete;

  void verifie_systeme();

public:

  Systeme(SupportADessin* const& sup);

  friend class VueOpenGL;

  void vider();

  void ajouter_Grain(GrainLJ* g);

  void ajouter_Obstacle(Obstacle* o);

  void ajouter_Source(Source* s);

  double adapt_dt(double const& dt, std::unique_ptr<GrainLJ> const& grain) const;

  void evolue(double const&);

  void stop_start_sources();

  void stop_start_obstacles();

  std::ostream& affiche(std::ostream& sortie) const;

  void dessine() override;

};

std::ostream& operator<<(std::ostream& sortie, Systeme const& s);

#endif

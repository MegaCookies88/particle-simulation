#ifndef Source_hpp
#define Source_hpp

#include "Dessinable.hpp"
#include "Objet.hpp"
#include "Aleatoire.hpp"
#include "Vecteur3D.hpp"
#include "GrainLJ.hpp"
#include "Grain.hpp"
#include "SupportADessin.hpp"
#include <vector>
#include <iostream>
#include <memory>

class Source : public Objet, public Dessinable{
private:

  Grain* g_ini;
  Vecteur3D vitesse_ini; //m.s
  double ec_vitesse; //m
  double ec_rayon; //m
  unsigned int debit;
  bool etat;

  static double rayon_arc; //m
  // source se deplace sur un segment de longueur rayon_arc

public:

  Source(Grain* const& g_ini, Vecteur3D const& position, Vecteur3D const& vitesse_ini,
     double ec_vitesse, double ec_rayon, unsigned int debit, SupportADessin* sup, bool e = true);

  ~Source(){
    delete g_ini;
  }

  friend class Systeme;

  void on();
  void off();

  void changer_support(SupportADessin* const& sup);

  void creation(std::vector<std::unique_ptr<GrainLJ>>& tab, double const& dt) const;

  virtual void dessine() override;

  std::ostream& affiche(std::ostream& sortie) const override;

};

#endif

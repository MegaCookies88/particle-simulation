#ifndef GrainLJTDeux_hpp
#define GrainLJTDeux_hpp

#include "GrainLJ.hpp"
#include "SupportADessin.hpp"

class GrainLJTDeux : public GrainLJ{
public:

  GrainLJTDeux(Grain const& g, SupportADessin* const& sup);

  void dessine() override;

  std::ostream& affiche(std::ostream& sortie) const override;


};

#endif

#ifndef GrainLJTUn_hpp
#define GrainLJTUn_hpp

#include "GrainLJ.hpp"
#include "SupportADessin.hpp"

class GrainLJTUn : public GrainLJ{
public:

  GrainLJTUn(Grain const& g, SupportADessin* sup);

  void dessine() override;

  std::ostream& affiche(std::ostream& sortie) const override;

};

#endif

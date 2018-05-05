#ifndef Milieu_hpp
#define Milieu_hpp

#include "Univers.hpp"
#include <string>

using namespace air;
using namespace eau;

class Milieu{
public:
  //masse volumique Kg/m3
  double m_vol_milieu;
  //viscosite dynamique Kg/m.s
  double visc_milieu;
  //constante comparaison vitesse pour calculer lambda
  double comp_milieu;

  Milieu(std::string const& milieu)
  : m_vol_milieu(0),
    visc_milieu(0),
    comp_milieu(0)
  {
    if(milieu == "air"){
      m_vol_milieu=m_vol_air;
      visc_milieu=visc_air;
      comp_milieu=comp_air;
    }
    if(milieu == "eau"){
      m_vol_milieu=m_vol_eau;
      visc_milieu=visc_eau;
      comp_milieu=comp_eau;
    }
  }
};

#endif

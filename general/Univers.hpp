#ifndef Univers_hpp
#define Univers_hpp

#include <cmath>

namespace univers{
  //gravite m/s2
  static double gravite = 9.81;
}

namespace air{
  //masse volumique Kg/m3
  static double m_vol_air = 1.3;
  //viscosite dynamique Kg/m.s
  static double visc_air = 1.8e-5;
  //constante comparaison vitesse pour calculer lambda
  static double comp_air = 3.7e-4;
};

namespace eau{
  //masse volumique Kg/m3
  static double m_vol_eau = 1e3;
  //viscosite dynamique Kg/m.s
  static double visc_eau = 1e-3;
  //constante comparaison vitesse pour calculer lambda
  static double comp_eau = 2.7e-5;
}

#endif

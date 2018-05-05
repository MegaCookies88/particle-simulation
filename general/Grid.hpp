#ifndef GRID_HPP
#define GRID_HPP

#include "Vecteur3D.hpp"
#include <vector>

class Cube{
private:
    Vecteur3D position;
    double cote;
public:
    Cube(Vecteur3D const& position = 0, double cote = 0);
};

class Grid{
private:
    std::vector<Cube> grille;
public:
    Grid(double distance_max, double pas_espace);
};

#endif

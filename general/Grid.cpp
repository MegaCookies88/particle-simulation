#include "Grid.hpp"
using namespace std;

Cube::Cube(Vecteur3D const& position, double cote)
: position(position),
  cote(cote)
{}

Grid::Grid(double distance_max, double pas_espace)
    : grille(vector<Cube>(0))
{
    Vecteur3D position(-distance_max,-distance_max,-distance_max);
    for(size_t i(0);i<distance_max+pas_espace;i++){
        //grille.push_back(Cube(position,pas_espace));
        position+=Vecteur3D();
    }
}

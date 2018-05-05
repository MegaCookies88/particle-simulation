#include "Vecteur3D.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Vecteur3D::Vecteur3D(const double& a,const double& b,const double& c)
  : x(a),
    y(b),
    z(c)
  {}

//methodes

double Vecteur3D::getX()const{
  return x;
}
double Vecteur3D::getY()const{
  return y;
}
double Vecteur3D::getZ()const{
  return z;
}

void Vecteur3D::set_coord(const unsigned int& n, const double& val){
    switch (n) {
        case 0: x=val; break;
        case 1: y=val; break;
        case 2: z=val; break;
    }
}

ostream& Vecteur3D::affiche(ostream& af) const{
  af <<x<<" "<<y<<" "<<z;
  return af;
}

double Vecteur3D::norme2() const{
    return x*x + y*y + z*z;
}

double Vecteur3D::norme() const{
    return sqrt(norme2());
}

Vecteur3D Vecteur3D::normalise() const{
  if(norme()!=0) return *this*(1.0/norme());
  return *this;
}

//surcharges

ostream& operator<<(ostream& sortie, const Vecteur3D& v){
  return v.affiche(sortie);
}

bool Vecteur3D::operator==(Vecteur3D const& v) const{
  return (x == v.x && y == v.y && z == v.z);
}

bool Vecteur3D::operator!=(Vecteur3D const& v) const{
  return !(*this==v);
}

const Vecteur3D& Vecteur3D::operator+=(const Vecteur3D& autre){
  x += autre.x;
  y += autre.y;
  z += autre.z;
  return *this;
}

const Vecteur3D& Vecteur3D::operator-=(const Vecteur3D& autre){
  x -= autre.x;
  y -= autre.y;
  z -= autre.z;
  return *this;
}

const Vecteur3D& Vecteur3D::operator*=(double const& w){
  x*=w;
  y*=w;
  z*=w;
  return *this;
}

const Vecteur3D operator+(Vecteur3D v, Vecteur3D const& w){
  return v+=w;
}

const Vecteur3D operator-(Vecteur3D v, Vecteur3D const& w){
  return v-=w;
}

const Vecteur3D operator*(Vecteur3D v, const double& w){
  return v*=w;
}

const Vecteur3D operator-(Vecteur3D const& v){
  return Vecteur3D(-v.getX(),-v.getY(),-v.getZ());
}

const Vecteur3D operator*(double const& w, Vecteur3D v){
  return v*=w;
}

double Vecteur3D::operator*(const Vecteur3D& autre) const{
  return x*autre.x + y*autre.y + z*autre.z;
}

const Vecteur3D Vecteur3D::operator^(const Vecteur3D& autre) const{
  return Vecteur3D(y*autre.z - z*autre.y, z*autre.x - x*autre.z, x*autre.y - y*autre.x);
}

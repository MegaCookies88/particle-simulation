#ifndef Vecteur3D_hpp
#define Vecteur3D_hpp

#include <iostream>

class Vecteur3D{
private:

    double x;
    double y;
    double z;

public:

    Vecteur3D(const double& x = 0,const double& y = 0,const double& z = 0);

    double getX()const;
    double getY()const;
    double getZ()const;

    void set_coord(const unsigned int& n, const double& val);

    std::ostream& affiche(std::ostream& af) const;

    double norme2() const;

    double norme() const;

    Vecteur3D normalise() const;

//surcharges

    bool operator==(Vecteur3D const& v) const;

    bool operator!=(Vecteur3D const& v) const;

    const Vecteur3D& operator+=(const Vecteur3D& v);

    const Vecteur3D& operator-=(const Vecteur3D& v);

//multiplication par un scalaire
    const Vecteur3D& operator*=(double const& w);

//produit scalaire
    double operator*(const Vecteur3D&) const;

//produit vectoriel
    const Vecteur3D operator^(const Vecteur3D&) const;

};

std::ostream& operator<<(std::ostream& sortie, const Vecteur3D& v);

const Vecteur3D operator+(Vecteur3D v, Vecteur3D const& w);

const Vecteur3D operator-(Vecteur3D v, Vecteur3D const& w);

//multiplication par un scalaire
const Vecteur3D operator*(Vecteur3D v, const double& w);
const Vecteur3D operator*(double const& w, Vecteur3D v);

//oppose du vecteur
const Vecteur3D operator-(Vecteur3D const& v);

#endif

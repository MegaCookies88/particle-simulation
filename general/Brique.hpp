#ifndef Brique_hpp
#define Brique_hpp

#include "Obstacle.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"
#include "Dalle.hpp"
#include <array>

class Brique : public Obstacle{
private:

    std::array<Dalle,6> faces;

public:

    Brique(Vecteur3D const& position, Vecteur3D const& vitesse, Vecteur3D const& normale,
        double longueur, double largeur, double hauteur, Vecteur3D const& direction, SupportADessin* sup);

    friend class VueOpenGL;

    virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

    std::ostream& affiche(std::ostream& sortie) const override;

    virtual void dessine() override;

    virtual void bouger(double const& dt) override;

};

#endif

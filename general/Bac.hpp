#ifndef Bac_hpp
#define Bac_hpp

#include "Obstacle.hpp"
#include "Vecteur3D.hpp"
#include "SupportADessin.hpp"
#include "Dalle.hpp"
#include "GrainLJ.hpp"
#include <array>
#include <memory>
#include <iostream>

class Bac : public Obstacle{
private:

    std::array<Dalle,5> faces;

public:

    Bac(Vecteur3D const& position, Vecteur3D const& vitesse,
        double longueur, double largeur, double hauteur, Vecteur3D const& direction, SupportADessin* sup);

    static Vecteur3D normale;

    friend class VueOpenGL;
    friend class Systeme;

    virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const override;

    std::ostream& affiche(std::ostream& sortie) const override;

    virtual void dessine() override;

    virtual void bouger(double const& dt) override;

    bool grain_dans_bac(Vecteur3D const& x_i) const;

    void changer_univers(std::unique_ptr<GrainLJ>& g) const override;

};

#endif

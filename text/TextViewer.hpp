#ifndef TextViewer_hpp
#define TextViewer_hpp

#include "SupportADessin.hpp"
#include <iostream>

class TextViewer : public SupportADessin{
public:

 virtual ~TextViewer() {}

 void dessine(GrainLJTUn const&) override;

 void dessine(GrainLJTDeux const&) override;

 void dessine(Systeme const&) override;

 void dessine(Plan const&) override;

 void dessine(Dalle const&) override;

 void dessine(Sphere const&) override;

 void dessine(Cylindre const&) override;

 void dessine(Source const&) override;

 void dessine(Brique const&) override;

 void dessine(Bac const&) override;

};

#endif

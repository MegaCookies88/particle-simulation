#ifndef SupportADessin_hpp
#define SupportADessin_hpp

class GrainLJTUn;
class GrainLJTDeux;
class Plan;
class Dalle;
class Cylindre;
class Sphere;
class Systeme;
class Source;
class Brique;
class Bac;

class SupportADessin
{
 public:

  virtual ~SupportADessin() {}

  virtual void dessine(GrainLJTUn const&) = 0;

  virtual void dessine(GrainLJTDeux const&) = 0;

  virtual void dessine(Systeme const&) = 0;

  virtual void dessine(Plan const&) = 0;

  virtual void dessine(Dalle const&) = 0;

  virtual void dessine(Sphere const&) = 0;

  virtual void dessine(Cylindre const&) = 0;

  virtual void dessine(Source const&) = 0;

  virtual void dessine(Brique const&) = 0;

  virtual void dessine(Bac const&) = 0;

};

#endif

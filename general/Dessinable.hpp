#ifndef Dessinable_hpp
#define Dessinable_hpp

class SupportADessin;

class Dessinable{
protected:

  SupportADessin* support;

public:

  Dessinable(SupportADessin* sup) : support(sup) {}

  virtual ~Dessinable() {}

  virtual void dessine() = 0;

  void changer_support(SupportADessin* sup){
     support=sup;
  }
};

#endif

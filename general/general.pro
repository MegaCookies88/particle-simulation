QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib

CONFIG = staticlib

SOURCES += \
    Aleatoire.cpp \
    Grain.cpp \
    GrainLJTUn.cpp \
    Plan.cpp  \
    Systeme.cpp \
    Cylindre.cpp \
    GrainLJ.cpp \
    Objet.cpp \
    Source.cpp \
    Vecteur3D.cpp \
    Dalle.cpp \
    GrainLJTDeux.cpp \
    Obstacle.cpp \
    Sphere.cpp \
    Bac.cpp \
    Brique.cpp \
    Grid.cpp

HEADERS += \
    Aleatoire.hpp \
    Univers.hpp \
    Milieu.hpp \
    Grain.hpp \
    GrainLJTUn.hpp \
    Plan.hpp  \
    Systeme.hpp \
    Cylindre.hpp \
    GrainLJ.hpp \
    Objet.hpp \
    Source.hpp \
    Vecteur3D.hpp \
    Dalle.hpp \
    GrainLJTDeux.hpp \
    Obstacle.hpp \
    Sphere.hpp \
    Dessinable.hpp \
    SupportADessin.hpp \
    Bac.hpp \
    Brique.hpp \
    Grid.hpp

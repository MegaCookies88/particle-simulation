QMAKE_CXXFLAGS += -std=c++11

TARGET = exerciceP11_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cpp \
    TextViewer.cpp

HEADERS += \
    TextViewer.hpp \
    ../general/Aleatoire.hpp \
    ../general/Univers.hpp \
    ../general/Milieu.hpp \
    ../general/Grain.hpp \
    ../general/GrainLJTUn.hpp \
    ../general/Plan.hpp  \
    ../general/Systeme.hpp \
    ../general/Cylindre.hpp \
    ../general/GrainLJ.hpp \
    ../general/Objet.hpp \
    ../general/Source.hpp \
    ../general/Vecteur3D.hpp \
    ../general/Dalle.hpp \
    ../general/GrainLJTDeux.hpp \
    ../general/Obstacle.hpp \
    ../general/Sphere.hpp \
    ../general/Dessinable.hpp \
    ../general/SupportADessin.hpp \
    ../general/Brique.hpp \
    ../general/Bac.hpp \

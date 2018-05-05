QT             += opengl
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulation_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
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
    ../general/Grid.hpp

RESOURCES += \
    resource.qrc

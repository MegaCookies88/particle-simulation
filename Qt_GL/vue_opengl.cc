#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include <cmath>
// ======================================================================
#include <iostream>

double VueOpenGL::scale = 100;

void VueOpenGL::dessine(Systeme const& systeme)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(auto const& obstacle : systeme.liste_obstacles){
    obstacle->dessine();
  }

  for(auto const& grain : systeme.liste_grains){
    grain->dessine();
  }
}

void VueOpenGL::dessine(GrainLJTUn const& grain)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();

  matrice.translate(scale*grain.getPosition().getX(), scale*grain.getPosition().getY(), scale*grain.getPosition().getZ());
  matrice.scale(scale*grain.getRayon());
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  dessineSphere(matrice, 0.9, 0.8, 0.6);
}

void VueOpenGL::dessine(GrainLJTDeux const& grain)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();

  matrice.translate(scale*grain.getPosition().getX(), scale*grain.getPosition().getY(), scale*grain.getPosition().getZ());
  matrice.scale(scale*grain.getRayon());
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  dessineSphere(matrice, 0.9, 0.7, 0.4);
}

void VueOpenGL::dessine(Sphere const& sphere)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();

  matrice.translate(scale*sphere.getPosition().getX(), scale*sphere.getPosition().getY(), scale*sphere.getPosition().getZ());
  matrice.scale(scale*sphere.rayon);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  dessineSphere(matrice, 0.6, 0.4, 0.0);
}

void VueOpenGL::dessine(Plan const& plan)
{
  double distance_max(1e3*Systeme::distance_max);
  Vecteur3D direction(plan.PointDuPlan()-plan.position);
  double r(0),v(0.5),b(0);
  if(!plan.invisible){
      dessinePlaque(Dalle(plan,distance_max,distance_max,direction),r,v,b);
      dessinePlaque(Dalle(plan,distance_max,distance_max,-direction),r,v,b);
      dessinePlaque(Dalle(plan,distance_max,distance_max,plan.normale^direction),r,v,b);
      dessinePlaque(Dalle(plan,distance_max,distance_max,direction^plan.normale),r,v,b);
  }
}

void VueOpenGL::dessine(Dalle const& dalle)
{
  dessinePlaque(dalle,0.7,0.4,0.1);
}

void VueOpenGL::dessine(Cylindre const& cylindre)
{
    QMatrix4x4 matrice;
    matrice.setToIdentity();

    Vecteur3D axe_rotation((cylindre.normale^Vecteur3D(0,1,0)).normalise());
    double angle_rotation(acos(cylindre.normale*Vecteur3D(0,1,0))*180.0/M_PI); // en degre
    matrice.translate(scale*cylindre.position.getX(),scale*cylindre.position.getY(),scale*cylindre.position.getZ());

    //on tourne la matrice de dessin tel que l axe y devient la normale du cylindre
    if(axe_rotation != Vecteur3D()) matrice.rotate(angle_rotation,axe_rotation.getX(),axe_rotation.getY(),axe_rotation.getZ());

    dessineCylindre(matrice,cylindre.rayon,cylindre.hauteur,0.5,0.5,0.5);
}

void VueOpenGL::dessine(Brique const& brique)
{
    for(size_t i(0); i<brique.faces.size(); i++){
        dessinePlaque(brique.faces[i],0.7,0.3,0.2);
    }
}

void VueOpenGL::dessine(Bac const& bac)
{
    dessinePlaque(bac.faces[0],0.2,0.4,1.0);
    for(size_t i(1); i<bac.faces.size(); i++){
        dessinePlaque(bac.faces[i],0.7,0.3,0.2);
    }
}

void VueOpenGL::dessine(Source const& source)
{
    Q_UNUSED(source);
}

// ======================================================================
void VueOpenGL::init()
{
  prog.addShaderFromSourceFile(QGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, -2.0, -5.0);
  matrice_vue.rotate(-90, 1.0, 0.0, 0.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

  glEnd();
}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue,double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessinePlaque(Dalle const& dalle, double rouge, double vert, double bleu, bool fill)
{
    QMatrix4x4 matrice;
    matrice.setToIdentity();

    Vecteur3D longeur(dalle.getPosition()+dalle.longueur*dalle.direction);
    Vecteur3D largeur(dalle.getPosition()+dalle.largeur*(dalle.normale^dalle.direction));

    matrice.scale(scale);
    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);

    if(fill){
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else{
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glBegin(GL_POLYGON);
    // coin bas gauche
    glVertex3f(dalle.getPosition().getX(), dalle.getPosition().getY(), dalle.getPosition().getZ());
    // coin haut gauche
    glVertex3f(largeur.getX(),largeur.getY(),largeur.getZ());
    // coin haut droit
    glVertex3f((largeur+longeur-dalle.getPosition()).getX(),
               (largeur+longeur-dalle.getPosition()).getY(),
               (largeur+longeur-dalle.getPosition()).getZ());
    // dernier coin
    glVertex3f(longeur.getX(),longeur.getY(),longeur.getZ());
    //dessiner l'autre face
    glVertex3f((largeur+longeur-dalle.getPosition()).getX(),
               (largeur+longeur-dalle.getPosition()).getY(),
               (largeur+longeur-dalle.getPosition()).getZ());
    glVertex3f(largeur.getX(),largeur.getY(),largeur.getZ());
    glVertex3f(dalle.getPosition().getX(), dalle.getPosition().getY(), dalle.getPosition().getZ());
    glEnd();
}

void VueOpenGL::dessineCylindre(QMatrix4x4& matrice, double const& rayon, double const& hauteur,double rouge, double vert, double bleu)
{
    matrice.scale(rayon*scale);
    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    prog.setAttributeValue(CouleurId, fmax(0.1,rouge-0.2), fmax(0.1,vert-0.2), fmax(0.1,bleu-0.2));

    //dessin des deux cercles
    for (double i=0.5*hauteur/rayon;i>=-0.5*hauteur/rayon;i-=hauteur/rayon) {
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0,i,0);
      for (int k=360;k>=0;k-=5) {
        glVertex3f(cos(M_PI/180*(k)),i,sin(M_PI/180*(k)));
      }
      for (int k=360;k>=0;k-=5) {
        glVertex3f(-cos(M_PI/180*(k)),i,sin(M_PI/180*(k)));
      }
      glEnd();
    }

    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);
    //dessin du bord du cylindre
    glBegin(GL_QUAD_STRIP);
    for (int j=0;j<=360;j+=5) {
      glVertex3f(cos(M_PI/180*(j)),-0.5*hauteur/rayon,sin(M_PI/180*(j)));
      glVertex3f(cos(M_PI/180*(j)),0.5*hauteur/rayon,sin(M_PI/180*(j)));
    }
    glEnd();
}

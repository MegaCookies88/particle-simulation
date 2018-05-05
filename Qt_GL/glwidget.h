#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.hpp"
#include <array>

class GLWidget : public QGLWidget
{
public:
  GLWidget(QWidget* parent = nullptr)
    : QGLWidget(parent)
    {}

  virtual ~GLWidget();

public:
  // objets à dessiner, faire évoluer
  //Systeme systeme;
  std::array<Systeme*,3> systeme = {{new Systeme(&vue), new Systeme(&vue), new Systeme(&vue)}};
  static size_t a_dessiner;

private:
  // Les 3 méthodes clés de la classe QGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;
  virtual void timerEvent(QTimerEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;

  //position souris
  QPointF lastMousePosition;
};

#endif // GLWIDGET_H

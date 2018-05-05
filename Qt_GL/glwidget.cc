#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

size_t GLWidget::a_dessiner = 1;

GLWidget::~GLWidget(){
  for(auto& s : systeme){
      delete s;
    }
}

// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);

  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  systeme[a_dessiner]->dessine();
}

// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(0.2);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    break;

  //pour activer/arreter les sources
  case Qt::Key_T:
    systeme[a_dessiner]->stop_start_sources();
    break;

  //pour activer/arreter le mvt des obstacles
  case Qt::Key_O:
    systeme[a_dessiner]->stop_start_obstacles();
      break;

  //pour changer de Systeme
  case Qt::Key_M:
    if(a_dessiner < systeme.size()-1){
        this->close();
        a_dessiner++;
        this->show();
      }
    break;
  case Qt::Key_N:
    if(a_dessiner > 0){
        this->close();
        a_dessiner--;
        this->show();
      }
    break;

  //vider le systeme
  case Qt::Key_V:
    systeme[a_dessiner]->vider();
      break;
  };

  updateGL(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  double dt = 0.0003;

  systeme[a_dessiner]->evolue(dt);
  updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() & Qt::LeftButton) {
    constexpr double petit_angle(.4); // en degrés

    // Récupère le mouvement relatif par rapport à la dernière position de la souris
    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);

    updateGL();
  }
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
    // dans ce cas le timer ne tourne pas alors on le lance
    timerId = startTimer(20);
    chronometre.restart();
  } else {
    // le timer tourne alors on l'arrête
    killTimer(timerId);
    timerId = 0;
  }
}

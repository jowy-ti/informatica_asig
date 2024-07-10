// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::iniEscena ()
{
  Estat_focusLoc = glGetUniformLocation (program->programId(), "Estat_focus");
  creaBuffersPatricio();
  creaBuffersTerra();
  creaBuffersCub();
  creaBuffersEsfera();

  // Paràmetres de l'escena - arbitraris
  centreEsc = glm::vec3 (0, 0, 0);
  radiEsc = sqrt(20*20+10*10+2*2);

  enviaPosFocus();
}

void MyGLWidget::enviaPosFocus()
{
  posFoc = glm::vec3(15, 10, 10);
  glUniform3fv (posfocusLoc, 1, &posFoc[0]);
  glUniform1i (Estat_focusLoc, Estat_focus);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = -0.5;
  camPlanta = false;
  ra = float(width())/height();
  radiEsc = sqrt(15*15+10*10+2*2);
  alfa = asin(radiEsc/(2*radiEsc));
  fov = 2*alfa;
  zn = radiEsc;
  zf = radiEsc*3;
  OBS = glm::vec3(15,2*radiEsc,10);
  VRP = glm::vec3(15,0,10);
  up = glm::vec3(0,0,-1);
  left = -radiEsc;
  right = radiEsc;
  bottom = -radiEsc;
  top = radiEsc;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  projectTransform ();
  viewTransform ();
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pintem l'arbre
  pintaArbre (Ar1);
  pintaArbre (Ar2);
  pintaArbre (Ar3);

  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h) 
{
#ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif

  ra = float(ample)/float(alt);
  if (ra < 1) {
    fov = 2*(atan(tan(alfa)/ra));
  }
  projectTransform();
}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(10, 0, 10));
  TG = glm::rotate(TG, angle_Pat, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::scale(TG, glm::vec3 (escala*2, escala*2, escala*2));
  TG = glm::translate(TG, -centreBasePat);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  
  glm::mat4 View = glm::mat4(1.f); 
  if (!camPlanta) {
    View = glm::translate(View, glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-15, 0, -10));

  }
  else
  {
    View = glm::lookAt(OBS, VRP, up);
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  
  glm::mat4 Proj;  // Matriu de projecció
  if (!camPlanta){
    Proj = glm::perspective(fov, ra, zn, zf);

  }
  else
  {
    Proj = glm::ortho(left, right, bottom, top, zn, zf);
  }
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      angle_Pat -= float(M_PI/16);
    break;
	}
  case Qt::Key_F: {
      if (Estat_focus == 0) Estat_focus = 1;
      else Estat_focus = 0;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      if (camPlanta) camPlanta = false;
      else camPlanta = true;
    break;
	}
  case Qt::Key_R: {
      angle_Pat = 0;
      Estat_focus = 0;
      camPlanta = false;
      enviaPosFocus();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camPlanta)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::Canvi_cam() {
  if (camPlanta) camPlanta = false;
  else camPlanta = true;
  update ();
}
void MyGLWidget::Move_Pat(int pos) {
  angle_Pat = -float(((2*M_PI)/32)*pos);
  update ();
}



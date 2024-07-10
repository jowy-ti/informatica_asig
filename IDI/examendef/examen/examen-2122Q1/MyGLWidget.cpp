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
  estat_focusLoc = glGetUniformLocation (program->programId(), "estat_focus");
  creaBuffersPatricio();
  creaBuffersAvio();
  creaBuffersHangar();
  creaBuffersTerra();

  // Paràmetres de l'escena - arbitraris
  centreEsc = glm::vec3 (15,0,12);
  radiEsc = sqrt(15*15+12*12+1.25*1.25);
}

void MyGLWidget::iniMaterialTerra()
{
  amb = glm::vec3(0.2,0.1,0.2);
  diff = glm::vec3(0.,0.6,0.6);
  spec = glm::vec3(1.,1.,1.);
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
  glm::mat4 TGP(1.f);
  TGP = glm::translate(TGP, glm::vec3 (15, alt_avio, 12));
  TGP = glm::rotate(TGP, angle_avio ,glm::vec3(0,1,0));
  TGP = glm::translate(TGP, glm::vec3 (10, 0, 0));
  
  glm::vec4 Prov = glm::vec4(0, 0.75, -3, 1);
  Prov = TGP*Prov;
  posFoc = glm::vec3(Prov.x, Prov.y, Prov.z);
  glUniform3fv (posfocusLoc, 1, &posFoc[0]);
  glUniform1i (estat_focusLoc, estat_focus);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = 0.5;
  camera2 = false;
  ra = float(width())/height();
  alfa = asin(radiEsc/(radiEsc*2));
  fov = 2*alfa;
  zn = radiEsc;
  zf = radiEsc*3;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  ExamGLWidget::paintGL();
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, centreEsc);
  TG = glm::rotate(TG, -float(M_PI/2),glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3 (escalaPat*2, escalaPat*2, escalaPat*2));
  TG = glm::translate(TG, -centreBasePat);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAvio ()
{
  TGAvio = glm::mat4(1.f);
  TGAvio = glm::translate(TGAvio, glm::vec3 (15, alt_avio, 12));
  TGAvio = glm::rotate(TGAvio , angle_avio ,glm::vec3(0,1,0));
  TGAvio = glm::translate(TGAvio, glm::vec3 (10, 0, 0));
  TGAvio = glm::scale(TGAvio, glm::vec3 (escalaAvio*1.5, escalaAvio*1.5, escalaAvio*1.5));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGAvio[0][0]);
  
}

void MyGLWidget::viewTransform ()
{
  
  glm::mat4 View = glm::mat4(1.f);
  if (!camera2) {
  
    View = glm::translate(View, glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);

  }
  else
  {
    View = glm::lookAt(glm::vec3(15,3,12), glm::vec3(14,3,12), glm::vec3(0,1,0));
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  
  glm::mat4 Proj;
  if (!camera2) {
  // Matriu de projecció
  
    Proj = glm::perspective(fov, ra, zn, zf);

  }
  else
  {
    Proj = glm::perspective(float(M_PI/2), ra, 0.f, zf);
  }
  
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      if (alt_avio < 5) alt_avio += 1;
    break;
	}
  case Qt::Key_Down: {
      if (alt_avio > 0) alt_avio -= 1;
    break;
	}
  case Qt::Key_Right: {
      angle_avio -= float(M_PI/16.f);
    break;
	}
  case Qt::Key_F: {
      if (estat_focus == 0) estat_focus = 1;
      else estat_focus = 0;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      if (!camera2) camera2 = true;
      else camera2 = false;
      viewTransform ();
      projectTransform ();
    break;
	}
  case Qt::Key_R: {
      // ...
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();
  if ((DoingInteractive == ROTATE) && !camera2)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / alt;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}



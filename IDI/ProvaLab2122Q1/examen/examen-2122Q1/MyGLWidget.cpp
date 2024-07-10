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
  creaBuffersPatricio();
  creaBuffersAvio();
  creaBuffersHangar();
  creaBuffersTerra();

  // Paràmetres de l'escena - arbitraris
  centreEsc = glm::vec3 (0, 0, 0);
  radiEsc = sqrt(20*20+10*10+2*2);
  rotAvio = 0.0;
  Yavio = 0.0;
  rotprova = 0.0;
  focus = false;
}

void MyGLWidget::iniMaterialTerra()
{
  // Donem valors al material del terra
  amb = glm::vec3(0,0.2,0.2);
  diff = glm::vec3(0,0.6,0.6);
  spec = glm::vec3(0.3,0.3,0.3);
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
    if (focus) posFoc = glm::vec3(0,0,0);
    else
    {
      calculaCapsaModel(true, avio, escalaAvio, centreBaseAvio);
      posFoc = glm::vec3 (-capsaAvioMin.x, -capsaAvioMin.y, -capsaAvioMin.z);
    }
    glUniform3fv (posfocusLoc, 1, &posFoc[0]);
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.5;
  angleX = -0.5;
  camera2 = false;
  ra = float(width())/height();
  fov = float(M_PI/3.0);
  zn = 19.25;
  zf = 65;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // inicialitzem llum
  enviaPosFocus();

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray (VAO_Patr);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

  // Pintem l'Avio
  glBindVertexArray (VAO_Avio);
  modelTransformAvio ();
  glDrawArrays(GL_TRIANGLES, 0, avio.faces().size()*3);

  // Pintem l'Hangar
  glBindVertexArray (VAO_Hang);
  modelTransformHangar ();
  glDrawArrays(GL_TRIANGLES, 0, hang.faces().size()*3);

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG(1.f);
  TG = glm::translate (TG, glm::vec3 (15, 0, 12));
  TG = glm::rotate (TG, -float(M_PI)/2, glm::vec3 (0,1,0));
  TG = glm::scale(TG, glm::vec3 (escalaPat*2.0f, escalaPat*2.0f, escalaPat*2.0f));
  TG = glm::translate(TG, -centreBasePat);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAvio ()
{
  TGAvio = glm::mat4(1.f);
  //TGAvio = glm::rotate (TGAvio, rotprova, glm::vec3 (0,1,0));
  TGAvio = glm::translate(TGAvio, glm::vec3 (15, 0, 12));
  TGAvio = glm::rotate (TGAvio, rotAvio, glm::vec3 (0,1,0));
  TGAvio = glm::translate (TGAvio, glm::vec3 (10, Yavio, 0));
  TGAvio = glm::scale(TGAvio, glm::vec3 (escalaAvio*1.5f, escalaAvio*1.5f, escalaAvio*1.5f));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGAvio[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (!camera2)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate (View, angleX, glm::vec3(1,0,0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-15, -1.25, -12));

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else
  {
    View = glm::lookAt (glm::vec3 (15, 2.5, 12), glm::vec3 (15, 3, 12), glm::vec3 (-1, 0, 0));
  }
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (!camera2)
  {
    Proj = glm::perspective(fov, ra, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
  else
  {
    Proj = glm::perspective(float(M_PI)/2, ra, 0.5f, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
      if (Yavio < 5.0f) ++Yavio;
      //rotprova += float(M_PI)/6;
    break;
	}
  case Qt::Key_Down: {
      if (Yavio > 0.0f) --Yavio;
    break;
	}
  case Qt::Key_Right: {
      rotAvio -= (float(M_PI)*11.25)/360;
      enviaPosFocus();
    break;
	}
  case Qt::Key_F: {
      focus = !focus;
      enviaPosFocus();
    break;
	}
  case Qt::Key_C: {
      camera2 = !camera2;
      viewTransform();
      //projectTransform();
    break;
	}
  case Qt::Key_R: {
      initializeGL();
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



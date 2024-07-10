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

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniform3fv (colfocusLoc, 1, &colFocus[0]);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  if (Pat_cub) {
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }

  // Pintem el cub
  else {
    for (int i = 0; i < 3; ++i) {
        glBindVertexArray(VAO_Cub);
        if (i == 0) modelTransformCub (4.0, anglecub1);
        else if (i == 1) modelTransformCub (5.0, anglecub2);
        else modelTransformCub (6.0, anglecub3);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);

  TG = rotate (TG, angle, glm::vec3(0,1,0));
  TG = translate (TG, posCub1);
  TG = scale (TG, glm::vec3(escala));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);

  TG = rotate (TG, anglePat, glm::vec3(0,1,0));
  TG = glm::translate(TG, posPat);
  TG = rotate (TG, float(-M_PI/2.f), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3 (escalaPat));
  TG = glm::scale(TG, glm::vec3 (escala, escala, escala));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    glm::mat4 Viewf;

    Viewf = glm::lookAt (glm::vec3(0.f,float(radiEsc*2),0.f), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f,0.f,0.f));

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &Viewf[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
      glm::mat4 Project = glm::ortho (-10.f, 10.f, -10.f, 10.f, zn, zf);
      glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Project[0][0]);
  }
}

void MyGLWidget::enviaColFocus () {
  if(Col_blanc_groc) {
          Col_blanc_groc = false;
          colFocus = glm::vec3(1,1,0);
    }
    else {
        Col_blanc_groc = true;
        colFocus = glm::vec3(1,1,1);
    }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      if(Pat_cub) Pat_cub = false;
      else Pat_cub = true;
    break;
	}
  case Qt::Key_1: {
      anglePat = 0;
    break;
	}
  case Qt::Key_2: {
      anglePat = anglecub2;
    break;
	}
  case Qt::Key_3: {
      anglePat = anglecub3;
    break;
	}
  case Qt::Key_F: {
      enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      if (camPlanta) camPlanta = false;
      else camPlanta = true;
      projectTransform ();
      viewTransform ();
    break;
	}
  case Qt::Key_Right: {
      anglecub1 += float(2*M_PI/3.f);
      anglecub2 += float(2*M_PI/3.f);
      anglecub3 += float(2*M_PI/3.f);
      anglePat += float(2*M_PI/3.f);
    break;
	}
  case Qt::Key_Left: {
      anglecub1 -= float(2*M_PI/3.f);
      anglecub2 -= float(2*M_PI/3.f);
      anglecub3 -= float(2*M_PI/3.f);
      anglePat -= float(2*M_PI/3.f);
    break;
	}
  case Qt::Key_R: {
    anglePat = 0;
    anglecub1 = 0;
    anglecub2 = float(2*M_PI/3.f);
    anglecub3 = float(4*M_PI/3.f);
    camPlanta = false;
    Col_blanc_groc = false;
    Pat_cub = false;
    enviaColFocus();
    projectTransform ();
    viewTransform ();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::asig_val(int val) {
  if (val == 0) anglePat = 0;
  else if (val == 1) anglePat = anglecub2;
  else anglePat = anglecub3;
  update();
}

void MyGLWidget::color_change() {
  if(Col_blanc_groc) {
        Col_blanc_groc = false;
        colFocus = glm::vec3(1,1,0);
  }
  else {
      Col_blanc_groc = true;
      colFocus = glm::vec3(1,1,1);
  }
  update();
}


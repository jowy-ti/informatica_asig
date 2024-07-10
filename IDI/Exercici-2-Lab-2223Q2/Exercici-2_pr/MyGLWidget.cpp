#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) {
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

void MyGLWidget::RickTransform() {
    
    glm::mat4 TG(1.0f);  
    TG = glm::translate(TG, glm::vec3(-2, 0, -2));
    TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
    TG = glm::rotate(TG, float(M_PI), glm::vec3(0,1,0));
    TG = glm::translate(TG, -centreBaseModels[RICK]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}
void MyGLWidget::VideoCameraTransform() {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-4, 3, -4));
    TG = glm::scale(TG, glm::vec3(escalaModels[VIDEOCAMERA]));
    TG = glm::rotate(TG, AngleCamy + float(M_PI/4), glm::vec3(0,1,0));
    TG = glm::rotate(TG, AngleCamx + float(M_PI/4), glm::vec3(1,0,0));
    TG = glm::translate(TG, -centreBaseModels[VIDEOCAMERA]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posMorty);
  TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
  TG = glm::rotate(TG, AngleMorty, glm::vec3(0.,1.,0.));
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform() {
    glm::mat4 View(1.0f);
    View = glm::translate(View, glm::vec3(0.,0.,-2*radiEscena));
    View = glm::rotate(View, factorAngleY + float(M_PI/4), glm::vec3(1.,0.,0.));
    View = glm::rotate(View, factorAngleX, glm::vec3(0.,1.,0.));
    View = glm::translate(View, -vrp);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
    
    makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
    	posMorty += glm::vec3(float(1.*sin(AngleMorty)),0., float(1.*cos(AngleMorty)))*glm::vec3(0.1);    	
        break;
    }
    case Qt::Key_Down: {
        posMorty -= glm::vec3(float(1.*sin(AngleMorty)),0., float(1.*cos(AngleMorty)))*glm::vec3(0.1);
        break;
    }
    case Qt::Key_Left: {
        AngleMorty += float(M_PI/4);
        break;
    }
    case Qt::Key_Right: {
        AngleMorty -= float(M_PI/4);
        break;
    }
    case Qt::Key_Q: {
        if (AngleCamy < float(M_PI/2)) AngleCamy += float(M_PI/180);
        break;
    }
    case Qt::Key_E: {
        if (AngleCamy > 0) AngleCamy -= float(M_PI/180);
        break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)    {
  makeCurrent();

  xClick = e->x();
  yClick = e->y();
  
  if(oldx < xClick) factorAngleX -= 0.025;
  
  else if(oldx > xClick) factorAngleX += 0.025;
  
  if(oldy < yClick) factorAngleY -= 0.025;
  
  else if(oldy > yClick) factorAngleY += 0.025;
  
  oldx = xClick;
  oldy = yClick;
  
  viewTransform();
  update ();
}

MyGLWidget::~MyGLWidget() {

}




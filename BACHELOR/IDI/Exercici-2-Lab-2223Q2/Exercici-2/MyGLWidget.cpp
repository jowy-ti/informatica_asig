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

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable(GL_DEPTH_TEST);
  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  iniEscena();
  iniCamera();
  glUniform1i(vrickLoc, VRick);
}

void MyGLWidget::paintGL() {

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  for (int i = 0; i < num_view; ++i) {
  
  if (i == 1) {
      glViewport ((ample*3)/4, (alt*3)/4, ample/4, alt/4);
      viewTransform_cam();
      projectTransform_cam();
      Verd_cam();
  }
  else {
      viewTransform();
      projectTransform();
      No_Verd_cam();
  }

  
  if (VRick) glUniform1i(vrickLoc, VRick);
  // Rick
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);
  
  glUniform1i(vrickLoc, 0);

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  
  // VideoCamera
  glBindVertexArray (VAO_models[VIDEOCAMERA]);
  VideoCameraTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);  
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // Paret
  ParetTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  }

  glBindVertexArray (0);
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
    TG = glm::translate(TG, base_cam);
    TG = glm::scale(TG, glm::vec3(escalaModels[VIDEOCAMERA]));
    TG = glm::rotate(TG, AngleCamy, glm::vec3(0,1,0));
    TG = glm::rotate(TG, AngleCamx, glm::vec3(1,0,0));
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

void MyGLWidget::viewTransform_cam() {
    Calc_VRP_cam();
    glm::mat4 View(1.0f);
    View = glm::lookAt (base_cam, VRP_cam, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform_cam() {
    glm::mat4 Proj(1.0f);
    Proj = glm::perspective(float(M_PI/3.), ra, 0.25f, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::Verd_cam() {
    glm::vec3 Verd = glm::vec3(0.f, 1.f, 0.f);
    glUniform3fv(verdLoc, 1, &Verd[0]);
}

void MyGLWidget::No_Verd_cam() {
    glm::vec3 Verd = glm::vec3(1.f, 1.f, 1.f);
    glUniform3fv(verdLoc, 1, &Verd[0]);
}

void MyGLWidget::Calc_VRP_cam() {
    VRP_cam = base_cam + glm::vec3(sin(AngleCamy)*3,-3.,cos(AngleCamy)*3);
}

void MyGLWidget::reiniciar() {
    VRick = 0;
    AngleCamy = float(M_PI/4);
    AngleCamx = float(M_PI/4);
    AngleMorty = 0;
    posMorty = glm::vec3(1,0,0);
    factorAngleY = 0;
    factorAngleX = 0;
    num_view = 1;
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
    case Qt::Key_C: {
        if (num_view == 1) num_view = 2;
        else num_view = 1;
        break;
    }
    case Qt::Key_G: {
        if (VRick == 0) VRick = 1;
        else VRick = 0;
        break;
    }
    case Qt::Key_R: {
        reiniciar();
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
  
  update ();
}

void MyGLWidget::carregaShaders() {
  LL2GLWidget::carregaShaders();
  
  verdLoc  = glGetUniformLocation (program->programId(), "Verd");
  vrickLoc  = glGetUniformLocation (program->programId(), "VRick");
}

MyGLWidget::~MyGLWidget() {

}

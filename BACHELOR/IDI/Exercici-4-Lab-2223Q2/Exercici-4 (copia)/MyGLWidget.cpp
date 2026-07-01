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

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  carregaShaders();
  PosF0Loc = glGetUniformLocation (program->programId(), "PosF0");
  PosF1Loc = glGetUniformLocation (program->programId(), "PosF1");
  PosF2Loc = glGetUniformLocation (program->programId(), "PosF2");
  PosF3Loc = glGetUniformLocation (program->programId(), "PosF3");
  IDBLoc = glGetUniformLocation (program->programId(), "IDB");
  ID0Loc = glGetUniformLocation (program->programId(), "ID0");
  ID1Loc = glGetUniformLocation (program->programId(), "ID1");
  ID2Loc = glGetUniformLocation (program->programId(), "ID2");
  ID3Loc = glGetUniformLocation (program->programId(), "ID3");
  
  glUniform1i (IDBLoc, IDB);
  glUniform1i (ID0Loc, ID0);
  glUniform1i (ID1Loc, ID1);
  glUniform1i (ID2Loc, ID2);
  glUniform1i (ID3Loc, ID3);
  
  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersDiscoBall();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();
}

void MyGLWidget::paintGL() {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 30);
  
  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  
  // FANTASMA
  glBindVertexArray (VAO_Fantasma);
  for (int i = 0; i < 2; ++i) {
    if (i == 0) modelTransformFantasma (1.0f);
    else modelTransformFantasma (9.0f);
    glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  }

  // DISCO BALL
  glBindVertexArray (VAO_DiscoBall);
  modelTransformDiscoBall ();
  glDrawArrays(GL_TRIANGLES, 0, discoBall.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformDiscoBall() {
  glm::mat4 TG, Trans;
  glm::vec4 PosF0, PosF1, PosF2, PosF3;
  
  TG = glm::translate(glm::mat4(1.f), centrebaseBola);
  TG = glm::scale(TG, glm::vec3(escalaDiscoBall, escalaDiscoBall, escalaDiscoBall));
  TG = glm::rotate(TG, angleyBola, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, -centreBaseDiscoBall);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  
  Trans = glm::rotate(glm::mat4(1.f), -angleyBola, glm::vec3(0, 1, 0));
  
  PosF0 = glm::vec4(PosID0, 1.) * Trans;
  PosF1 = glm::vec4(PosID1, 1.) * Trans;
  PosF2 = glm::vec4(PosID2, 1.) * Trans;
  PosF3 = glm::vec4(PosID3, 1.) * Trans;

  PosF0 = PosF0 + glm::vec4(centreBola, 0.);
  PosF1 = PosF1 + glm::vec4(centreBola, 0.);
  PosF2 = PosF2 + glm::vec4(centreBola, 0.);
  PosF3 = PosF3 + glm::vec4(centreBola, 0.);
  
  glUniform4fv (PosF0Loc, 1, &PosF0[0]);
  
  glUniform4fv (PosF1Loc, 1, &PosF1[0]);
  
  glUniform4fv (PosF2Loc, 1, &PosF2[0]);
  
  glUniform4fv (PosF3Loc, 1, &PosF3[0]);
}

void MyGLWidget::modelTransformMorty() {
  
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG = glm::scale(TG, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG = glm::rotate(TG, angleyMortyFant, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformFantasma(float posX) {
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.0f), glm::vec3(posX,0.5,5));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::rotate(TG, angleyMortyFant, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      angleyMortyFant += float(M_PI/8.f);
    break;
	}
  case Qt::Key_D: {
      angleyMortyFant -= float(M_PI/8.f);
    break;
	}
  case Qt::Key_E: {
      if (IDB == 1) IDB = 0;
      else IDB = 1;
      glUniform1i (IDBLoc, IDB);
    break;
	}
  case Qt::Key_B: {
      if (ID3 == 1) {
        if (ID0 == 1) ID0 = 0;
        else if (ID1 == 1) ID1 = 0;
        else if (ID2 == 1) ID2 = 0;
        else if (ID3 == 1) ID3 = 0;
      }
      else {
        if (ID0 == 0) ID0 = 1;
        else if (ID1 == 0) ID1 = 1;
        else if (ID2 == 0) ID2 = 1;
        else if (ID3 == 0) ID3 = 1;
      }
      glUniform1i (ID0Loc, ID0);
      glUniform1i (ID1Loc, ID1);
      glUniform1i (ID2Loc, ID2);
      glUniform1i (ID3Loc, ID3);
    break;
	}	
  case Qt::Key_R: {
    angleyBola += float((M_PI/360.f)*5.f);
    break;
	}
  case Qt::Key_S: {
      // ...
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

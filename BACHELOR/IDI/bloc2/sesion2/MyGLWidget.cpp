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

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  ini_camera();
}

void MyGLWidget::ini_camera(){
    OBS = glm::vec3(0,0,2);
    VRP = glm::vec3(0,0,0);
    up = glm::vec3(0,1,0);
    FOV = float(M_PI)/2.0f;
    ra = 1.0f;
    znear = 0.4f;
    zfar = 3.0f;
    viewTransform();
    projectTransform();
}

void MyGLWidget::paintGL()
{
    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);

    // Carreguem la transformació de model
    modelTransform2 ();

    // Activem el VAO per a pintar la caseta
    glBindVertexArray (VAO_Homer);

    // pintem
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

    modelTransform();
    glBindVertexArray (VAO_Terra);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray (0);
}

void MyGLWidget::creaBuffers()
{
    m.load("./Model/HomerProves.obj");
    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Homer);
    glBindVertexArray(VAO_Homer);

    GLuint VBO_Homer[2];
    glGenBuffers(2, VBO_Homer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glm::vec3 posicionsuelo[6] = {
        glm::vec3(-2.0, -1.0, -2.0),
        glm::vec3(-2.0, -1.0, 2.0),
        glm::vec3(2.0, -1.0, -2.0),
        glm::vec3(-2.0, -1.0, 2.0),
        glm::vec3(2.0, -1.0, -2.0),
        glm::vec3(2.0, -1.0, 2.0)
    };
    glm::vec3 colorsuelo[6] = {
        glm::vec3(1,0,1),
        glm::vec3(1,0,1),
        glm::vec3(1,0,1),
        glm::vec3(1,0,1),
        glm::vec3(1,0,1),
        glm::vec3(1,0,1)
    };

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(1, &VBO_Terra[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicionsuelo), posicionsuelo, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glGenBuffers(1, &VBO_Terra[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorsuelo), colorsuelo, GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    glBindVertexArray (0);
}

void MyGLWidget::projectTransform() {
    // glm::perspective (FOV en radians, ra window, znear, zfar)
    glm::mat4 Proj = glm::perspective (FOV, ra, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 View = glm::lookAt (OBS, VRP, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::modelTransform () {
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform2 () {
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala));
  transform = glm::rotate(transform, angle, glm::vec3(0., 1., 0.));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::carregaShaders() {
    BL2GLWidget::carregaShaders();

    projLoc =glGetUniformLocation(program->programId(), "proj");
    viewLoc =glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::keyPressEvent (QKeyEvent *event) {
    
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_R: { // escalar a més gran
      angle += float(M_PI/4);
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

MyGLWidget::~MyGLWidget() {
}



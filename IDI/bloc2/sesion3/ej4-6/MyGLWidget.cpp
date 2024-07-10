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
    r = float(distance(min2,max2)/2.0);
    VRP = glm::vec3((min2.x+max2.x)/2, (min2.y+max2.y)/2, (min2.z+max2.z)/2);
    OBS = glm::vec3(VRP.x, VRP.y+2*r, VRP.z);
    up = glm::vec3(0,1,0);
    alfa = float(asin(r/(2*r)));
    FOV = 2*alfa;
    ra = 1.0f;
    znear = 3.f;
    zfar = 9.f;
    top = r/2;
    bottom = -r/2;
    left = -r/2;
    right = r/2;
}

void MyGLWidget::resizeGL (int w, int h) {
    glViewport(0, 0, w, h);
    ra = float (w) / float (h);
    if (ra < 1) FOV = float(2*(atan(tan(alfa)/ra)));
    if (ra >= 1) {
        right = (r/2)*ra;
        left = -right;
    }
    if (ra <= 1) {
        top = (r/2)/ra;
        bottom = -top;
    }
}

void MyGLWidget::paintGL()
{
    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
    viewTransform();
    projectTransform();

    // Carreguem la transformació de model
    modelTransform2 ();

    // Activem el VAO per a pintar la caseta
    glBindVertexArray (VAO_Patricio);

    // pintem
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

    modelTransform();
    glBindVertexArray (VAO_Terra);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray (0);
}

void MyGLWidget::creaBuffers()
{
    m.load("./Model/Patricio.obj");
    
    calcCapsaContenidora(m,patrMin,patrMax);
    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Patricio);
    glBindVertexArray(VAO_Patricio);

    GLuint VBO_Patricio[2];
    glGenBuffers(2, VBO_Patricio);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glm::vec3 posicionsuelo[6] = {
        glm::vec3(-2.5, 0, -2.5),
        glm::vec3(-2.5, 0, 2.5),
        glm::vec3(2.5, 0, -2.5),
        glm::vec3(-2.5, 0, 2.5),
        glm::vec3(2.5, 0, -2.5),
        glm::vec3(2.5, 0, 2.5)
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

void MyGLWidget::calcCapsaContenidora(const Model &model,glm::vec3& min,glm::vec3& max) {
    
    double x,y,z;
    min.x = max.x = model.vertices()[0];
    min.y = max.y = model.vertices()[1];
    min.z = max.z = model.vertices()[2];
    
    for(unsigned int i = 3;i<model.vertices().size();i+=3) {
        x = model.vertices()[i];
        y = model.vertices()[i+1];
        z = model.vertices()[i+2];
        if(x<min.x) min.x = x;
        else if (x>max.x) max.x = x;
        if(y<min.y) min.y = y;
        else if (y>max.y) max.y = y;
        if(z<min.z) min.z = z;
        else if (z>max.z) max.z = z;
    }
    pos = glm::vec3 ((max.x+min.x)/2, min.y, (max.z+min.z)/2);
    float alçada = max.y-min.y;
    escala_Pat = alçada/4;
    escala_Pat = 1/escala_Pat;
    min2 = glm::vec3 (-2.5, 0, -2.5);
    max2 = glm::vec3 (2.5, 4, 2.5);
}

void MyGLWidget::projectTransform() {
    // glm::perspective (FOV en radians, ra window, znear, zfar)
    glm::mat4 Proj;
    if (tipus_proj == 0) Proj = glm::perspective (FOV, ra, znear, zfar);
    else Proj = glm::ortho (left, right, bottom, top, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
    //glm::mat4 View = glm::mat4(1.f);
    //View = glm::translate (View, glm::vec3(0,0,-r*2));
    //View = glm::rotate(View, -float(M_PI/2), glm::vec3(0., 0., 1.));
    //View = glm::rotate(View, float(M_PI/2), glm::vec3(0., 1., 0.));
    //View = glm::translate (View, glm::vec3(-VRP.x, -VRP.y, -VRP.z));
    glm::mat4 View = glm::lookAt (OBS, VRP, glm::vec3(1,0,0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::modelTransform () {
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala_Ter));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform2 () {
  // Matriu de transformació de model
    
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, angle, glm::vec3(0., 1., 0.));
  transform = glm::scale(transform, glm::vec3(escala_Pat));
  transform = translate (transform, -pos);
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
    case Qt::Key_O: { // escalar a més gran
      tipus_proj = (tipus_proj+1)%2;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

MyGLWidget::~MyGLWidget() {
}



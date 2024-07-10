// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();
    
    virtual void initializeGL ();
    virtual void carregaShaders();
    virtual void paintGL();
    virtual void creaBuffers();
    virtual void modelTransform();
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void resizeGL (int w, int h);

    void projectTransform();
    void viewTransform();
    void ini_camera();
    void modelTransform2(int i);
    void calcCapsaContenidora(const Model &model);
    void mouseMoveEvent(QMouseEvent *e);
    void calcEsfera();

    GLuint VAO_Patricio, VAO_Terra;
    Model m;

    GLuint projLoc, viewLoc;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar, r, alfa, left, right, top, bottom;
    float angle = 0;
    float angle1 = float(M_PI);
    float angle2 = float(M_PI/2);
    float escala_Pat = 1.f;
    float escala_Ter = 1.f;
    int tipus_proj = 0;
    float rx, ry, sx, sy;
    
    glm::vec3 pos, max2, min2;
    glm::vec3 pos0 = glm::vec3(2.f,0.f,2.f);
    glm::vec3 pos1 = glm::vec3(-2.f,0.f,-2.f);

  private:
    int printOglError(const char file[], int line, const char func[]);
};

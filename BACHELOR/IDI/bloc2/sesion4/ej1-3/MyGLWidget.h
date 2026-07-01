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
    void modelTransform2();
    void calcCapsaContenidora(const Model &model,glm::vec3& min,glm::vec3& max);
    void mouseMoveEvent(QMouseEvent *e);

    GLuint VAO_Patricio, VAO_Terra;
    Model m;

    GLuint projLoc, viewLoc;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar, r, alfa, left, right, top, bottom;
    float angle = 0;
    float escala_Pat = 1.f;
    float escala_Ter = 1.f;
    int tipus_proj = 0;
    float rx, ry, sx, sy;
    
    glm::vec3 pos, patrMin, patrMax, max2, min2;

  private:
    int printOglError(const char file[], int line, const char func[]);
};

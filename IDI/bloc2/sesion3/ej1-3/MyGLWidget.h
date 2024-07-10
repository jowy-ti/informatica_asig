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

    GLuint VAO_Homer, VAO_Terra;
    Model m;

    GLuint projLoc, viewLoc;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar, r, alfa;
    float angle = 0;
    float escala = 1.f;

  private:
    int printOglError(const char file[], int line, const char func[]);
};

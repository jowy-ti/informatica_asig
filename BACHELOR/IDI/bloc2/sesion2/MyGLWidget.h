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

    void projectTransform();
    void viewTransform();
    void ini_camera();
    void modelTransform2();

    GLuint VAO_Homer, VAO_Terra;
    Model m;

    GLuint projLoc, viewLoc;

    glm::vec3 OBS, VRP, up;
    float FOV, ra, znear, zfar;
    float angle = 0;
    float escala = 0.5f;

  private:
    int printOglError(const char file[], int line, const char func[]);
};

// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra ();
    virtual void initializeGL();
    virtual void paintGL ();
    void iniFocus();

    glm::vec3 posF = glm::vec3 (1,1,1);
    glm::vec3 colF = glm::vec3(0.8, 0.8, 0.8);
    int SCA = 0;

    GLuint colorFocusLoc, posFocusLoc, SCALoc;

  private:
    int printOglError(const char file[], int line, const char func[]);
};

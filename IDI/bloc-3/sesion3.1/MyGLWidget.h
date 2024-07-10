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
    virtual void carregaShaders();
    virtual void initializeGL();
    
    void Set_col_pos_Focus();
    
    GLuint colorFocusLoc, posFocusLoc;
    glm::vec3 posF = glm::vec3(1, 0, 1);
    glm::vec3 colF = glm::vec3(0.8, 0.8, 0.8);

  private:
    int printOglError(const char file[], int line, const char func[]);
};

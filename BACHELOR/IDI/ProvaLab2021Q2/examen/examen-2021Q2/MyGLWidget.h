#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();
    
    public
    slots:
    void Canvi_cam();
    void Move_Pat(int pos);

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void resizeGL (int w, int h);

    virtual void modelTransformPatricio ();
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    
    GLuint Estat_focusLoc;
    float alfa, left, right, bottom, top;
    int Estat_focus = 0;
    float angle_Pat = 0;
    glm::vec3 OBS, VRP, up;
    glm::vec3 Ar1 = glm::vec3(10,0,10);
    glm::vec3 Ar2 = glm::vec3(20,0,5);
    glm::vec3 Ar3 = glm::vec3(25,0,15);

  private:
    int printOglError(const char file[], int line, const char func[]);
};

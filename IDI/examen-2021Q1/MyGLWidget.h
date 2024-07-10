#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();
    
    public
    slots:
    void asig_val(int val);
    void color_change();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void enviaColFocus ();

    glm::vec3 posCub1 = glm::vec3(5,0,0);
    glm::vec3 posPat = glm::vec3(5,0,0);
    float escalaPat = 2;
    float anglePat = 0;
    float anglecub1 = 0;
    float anglecub2 = float(2*M_PI/3.f);
    float anglecub3 = float(4*M_PI/3.f);

    GLuint colFocusLoc;
    glm::vec3 colFocus = glm::vec3(1,1,1);

    bool Col_blanc_groc = false;
    bool Pat_cub = false;

    float right = radiEsc;
    float left = -radiEsc;
    float top = radiEsc;
    float bottom = -radiEsc;

    glm::vec3 OBS = glm::vec3(0.f,float(radiEsc*2),0.f);

  private:
    int printOglError(const char file[], int line, const char func[]);
};

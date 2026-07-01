#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();
    
  protected:
    virtual void RickTransform();
    virtual void VideoCameraTransform();
    virtual void viewTransform();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void MortyTransform();
    virtual void paintGL();
    virtual void carregaShaders();
    virtual void initializeGL();
    
    GLuint verdLoc;
    GLuint vrickLoc;
    
    void viewTransform_cam();
    void projectTransform_cam();
    void Calc_VRP_cam();
    void Verd_cam();
    void No_Verd_cam();
    void reiniciar();
    
    float oldx = 0, oldy = 0;
    float AngleCamy = float(M_PI/4), AngleCamx = float(M_PI/4), AngleMorty = 0;
    int VRick = 0;
    int num_view = 1;
    
    glm::vec3 base_cam = glm::vec3(-4., 3., -4.);
    glm::vec3 VRP_cam;
    
  private:
    int printOglError(const char file[], int line, const char func[]);
    
};

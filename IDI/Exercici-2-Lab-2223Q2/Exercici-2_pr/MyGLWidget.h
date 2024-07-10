#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

    
    virtual void RickTransform();
    virtual void VideoCameraTransform();
    virtual void viewTransform();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void MortyTransform();
    
  protected:

    float oldx = 0, oldy = 0;
    float AngleCamy = 0, AngleCamx = 0, AngleMorty = 0;
  private:

  
    int printOglError(const char file[], int line, const char func[]);
    
};

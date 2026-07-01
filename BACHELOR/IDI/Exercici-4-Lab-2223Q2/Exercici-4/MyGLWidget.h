// MyGLWidget.h
#include "LL4GLWidget.h"
#include <QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
    
  public
  slots:
    void TimeOut();
    
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformDiscoBall ();
    virtual void modelTransformMorty();
    virtual void modelTransformFantasma(float posX);
    virtual void paintGL();
    virtual void initializeGL();
    void girBola();
    void apagar_encendre_llum();
    
    float angleyBola = 0;
    float angleyMortyFant = 0;
    glm::vec3 centreBola = glm::vec3(5.,5.75,5.);
    glm::vec3 centrebaseBola = glm::vec3(5.,5.,5.);
    glm::vec3 PosID0 = glm::vec3(1.2,0,0);
    glm::vec3 PosID1 = glm::vec3(-1.2,0,0);
    glm::vec3 PosID2 = glm::vec3(0,0,1.2);
    glm::vec3 PosID3 = glm::vec3(0,0,-1.2);
    
    GLuint PosF0Loc, PosF1Loc, PosF2Loc, PosF3Loc;
    GLuint IDBLoc, ID0Loc, ID1Loc, ID2Loc, ID3Loc;
    int IDB = 1, ID0 = 1, ID1 = 1, ID2 = 1, ID3 = 1;
    
    bool go = false;
    
  private:
    int printOglError(const char file[], int line, const char func[]);
    
    QTimer *timer;
};

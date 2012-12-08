#ifndef CONTROL_HH
#define CONTROL_HH

#include <QKeyEvent>
#include "glwidget.hh"
#include "cameracontrol.hh"
#include "camera.hh"
#include "physiccontrol.hh"

class GLWidget;
class Camera;
class CameraControl;

class Control
{
public:
    Control(GLWidget *widget);
    ~Control();

    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);
    void mousePressEvent   ( QMouseEvent* pMouseEvent);
    void mouseReleaseEvent ( QMouseEvent* pMouseEvent);
    void mouseMoveEvent    ( QMouseEvent* pMouseEvent, const QPoint& oRelative);
    void wheelEvent        ( QWheelEvent* pWheelEvent);

    void setAimCam( bool _aim ) { aimCam = _aim; }
    void update(float _elapsedTime);

    vector<Banana*> *getBananas() { return mpPhysics->getBananas(); }
    vector<Building*> *getBuildings() { return mpPhysics->getBuildings(); }
    vector<Gorilla*> *getGorillas() { return mpPhysics->getGorillas(); }
    void addBuilding( Building *_b ) { mpPhysics->addBuilding( _b ); }
    void addBanana( Banana *_b ) { mpPhysics->addBanana( _b ); }
    void addGorilla( Gorilla *_b ) { mpPhysics->addGorilla( _b ); }

    Camera *getCamera();
    Gorilla *getActiveGorilla();
    PhysicControl *getPhysics();

private:
    CameraControl *mpCameraControl;
    GLWidget *mpWidget;
    PhysicControl *mpPhysics;
    bool keys[7];
    bool aimCam;
    bool shot;
    float dT;
};

#endif // CONTROL_HH

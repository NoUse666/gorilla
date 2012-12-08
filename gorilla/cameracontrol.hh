#ifndef CAMERACONTROL_HH
#define CAMERACONTROL_HH

#include <QKeyEvent>
#include "glwidget.hh"
#include "camera.hh"
#include "control.hh"
#include "functions.hh"

class GLWidget;
class Control;

using namespace func;

class CameraControl
{
public:
    CameraControl(GLWidget *widget, Control *_control);
    ~CameraControl();

    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);
    void mousePressEvent   ( QMouseEvent* pMouseEvent);
    void mouseReleaseEvent ( QMouseEvent* pMouseEvent);
    void mouseMoveEvent    ( QMouseEvent* pMouseEvent, const QPoint& oRelative);
    void wheelEvent        ( QWheelEvent* pWheelEvent);

    inline void setWidget(GLWidget *widget) { mpWidget = widget; }
    inline Camera *getCamera() { return mpCamera; }

    void update(float _elapsedTime);

    void rotateCamX( float angle );
    void rotateCamY( float angle );
    void rotateAround( vec3 _p, float _deg, vec3 _axis );

    void camFollow( Banana *b );

private:

    bool key[6];
    bool follow;
    Banana *followBanana;
    Camera *mpCamera;
    Control *mpControl;
    GLWidget *mpWidget;
};

#endif // CAMERACONTROL_HH

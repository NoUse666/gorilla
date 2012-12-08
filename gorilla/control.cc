#include "control.hh"
#include <iostream>

Control::Control( GLWidget *widget ):
    mpWidget(widget),
    mpCameraControl(new CameraControl(widget, this)),
    aimCam(true),
    mpPhysics(new PhysicControl()),
    shot( false )
{
    for (int i=0; i<7; i++) keys[i] = false;
}

Control::~Control()
{
}

int camOnGorilla = 0;

void Control::keyPressed(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        //camOnGorilla = (camOnGorilla+1) % 4;
        getActiveGorilla()->moveCameraTo( getCamera() );
        aimCam = true;
    }
    if ( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter )
    {
        keys[6] = true;
    }
    if ( event->key() == Qt::Key_Up)
    {
        keys[0] = true;
    }
    if ( event->key() == Qt::Key_Down )
    {
        keys[1] = true;
    }
    if ( event->key() == Qt::Key_Left )
    {
        keys[2] = true;
    }
    if ( event->key() == Qt::Key_Right )
    {
        keys[3] = true;
    }
    if ( event->key() == Qt::Key_Plus )
    {
        keys[4] = true;
    }
    if ( event->key() == Qt::Key_Minus )
    {
        keys[5] = true;
    }
    mpCameraControl->keyPressed(event);
}

void Control::keyReleased(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Up)
    {
        keys[0] = false;
    }
    if ( event->key() == Qt::Key_Down )
    {
        keys[1] = false;
    }
    if ( event->key() == Qt::Key_Left )
    {
        keys[2] = false;
    }
    if ( event->key() == Qt::Key_Right )
    {
        keys[3] = false;
    }
    if ( event->key() == Qt::Key_Plus )
    {
        keys[4] = false;
    }
    if ( event->key() == Qt::Key_Minus )
    {
        keys[5] = false;
    }
    if ( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter )
    {
        keys[6] = false;
    }
    mpCameraControl->keyReleased(event);
}

void Control::mousePressEvent(QMouseEvent *pMouseEvent)
{
    mpCameraControl->mousePressEvent(pMouseEvent);
}

void Control::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    mpCameraControl->mouseReleaseEvent(pMouseEvent);
}

void Control::mouseMoveEvent(QMouseEvent *pMouseEvent, const QPoint &oRelative)
{
    mpCameraControl->mouseMoveEvent(pMouseEvent, oRelative);
}

void Control::wheelEvent(QWheelEvent *pWheelEvent)
{
    mpCameraControl->wheelEvent(pWheelEvent);
}


void Control::update(float _elapsedTime)
{
    mpPhysics->update(_elapsedTime);
    mpCameraControl->update(_elapsedTime);

    if (keys[0])
    {
        float yaw = getActiveGorilla()->getYaw();
        float pitch = getActiveGorilla()->getPitch() + 30*_elapsedTime;
        getActiveGorilla()->setAim( yaw, pitch );
        //mpWidget->getActiveGorilla()->moveCameraTo( getCamera() );
    }
    if (keys[1])
    {
        float yaw = getActiveGorilla()->getYaw();
        float pitch = getActiveGorilla()->getPitch() - 30*_elapsedTime;
        getActiveGorilla()->setAim( yaw, pitch );
        //mpWidget->getActiveGorilla()->moveCameraTo( getCamera() );
    }
    if (keys[2])
    {
        float yaw = getActiveGorilla()->getYaw() - 30*_elapsedTime;
        float pitch = getActiveGorilla()->getPitch();
        getActiveGorilla()->setAim( yaw, pitch );
        if (aimCam) mpCameraControl->rotateAround( getActiveGorilla()->getPos() + vec3(0,0.75f,0), -30*_elapsedTime, vec3(0,1,0) );
    }
    if (keys[3])
    {
        float yaw = getActiveGorilla()->getYaw() + 30*_elapsedTime;
        float pitch = getActiveGorilla()->getPitch();
        getActiveGorilla()->setAim( yaw, pitch );
        if (aimCam) mpCameraControl->rotateAround( getActiveGorilla()->getPos() + vec3(0,0.75f,0), 30*_elapsedTime, vec3(0,1,0) );
    }
    if (keys[4])
    {
        getActiveGorilla()->setStrength( getActiveGorilla()->getStrength() + 0.2f * _elapsedTime);
    }
    if (keys[5])
    {
        getActiveGorilla()->setStrength( getActiveGorilla()->getStrength() - 0.2f * _elapsedTime);
    }
    if ( keys[6] )
    {
        if ( !shot || mpPhysics->getGorillas()->size() == 1 )
        {
            mpPhysics->addBanana(new Banana( getActiveGorilla()->getDirection().normalize() * getActiveGorilla()->getStrength()*40,
                                         getActiveGorilla()->getPos()+vec3(0,0.35f,0) + getActiveGorilla()->getDirection().normalize() * 0.1f,
                                         getActiveGorilla()->getPitch(), 50, 5));

            if ( aimCam ) mpCameraControl->camFollow( (Banana*)*mpPhysics->getBananas()->begin() );

            dT = 0;

            shot = true;
        }
    }

    if ( shot && mpPhysics->getBananas()->empty() )
    {
        if ( dT > 3.f )
        {
            shot = false;
            mpPhysics->nextGorilla();
            Gorilla *g = getActiveGorilla();
            if ( g != NULL )
                g->moveCameraTo( getCamera() );
            aimCam = true;
        }
        else
            dT += _elapsedTime;
    }

}

Camera *Control::getCamera()
{
    return mpCameraControl->getCamera();
}

Gorilla *Control::getActiveGorilla()
{
    for ( vector<Gorilla*>::iterator it = mpPhysics->getGorillas()->begin(); it < mpPhysics->getGorillas()->end(); it++ )
    {
        Gorilla *g = (Gorilla*)*it;
        if ( g->isActive() )
            return g;
    }
}

PhysicControl *Control::getPhysics()
{
    return mpPhysics;
}

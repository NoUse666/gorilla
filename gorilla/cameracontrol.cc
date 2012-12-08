#include "cameracontrol.hh"
#include <math.h>
#include <iostream>

float mWalkSpeed = 2.0f;

CameraControl::CameraControl(GLWidget *widget, Control *_control):
    mpWidget(widget),
    mpCamera(new Camera),
    mpControl(_control),
    follow( false )
{
    for (int i=0; i<6; i++)
        key[i] = false;
}

CameraControl::~CameraControl()
{
}

void CameraControl::keyPressed(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        key[0] = true;
        mpControl->setAimCam( false );
        break;
    case Qt::Key_S:
        key[1] = true;
        mpControl->setAimCam( false );
        break;
    case Qt::Key_A:
        key[2] = true;
        mpControl->setAimCam( false );
        break;
    case Qt::Key_D:
        key[3] = true;
        mpControl->setAimCam( false );
        break;
    case Qt::Key_Shift:
        mWalkSpeed *= 7.f;
        break;
    }
}

void CameraControl::keyReleased(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        key[0] = false;
        break;
    case Qt::Key_S:
        key[1] = false;
        break;
    case Qt::Key_A:
        key[2] = false;
        break;
    case Qt::Key_D:
        key[3] = false;
        break;
    case Qt::Key_Shift:
        mWalkSpeed /= 7.f;
        break;
    }
}

void CameraControl::mousePressEvent(QMouseEvent *pMouseEvent)
{
}

void CameraControl::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
}

void CameraControl::mouseMoveEvent(QMouseEvent *pMouseEvent, const QPoint &oRelative)
{
    float mRotationSpeed = 1.f;
    float relativeX = (float)(oRelative.x());
    float relativeY = (float)(oRelative.y());

    if(pMouseEvent->buttons() & Qt::RightButton )
    {
        if ( !follow )
        {
            mpCamera->setPitch(mpCamera->getPitch() - relativeY * mRotationSpeed);
            mpCamera->setYaw(mpCamera->getYaw() + relativeX * mRotationSpeed);
            mpControl->setAimCam( false );
        }
        else
        {
            if ( followBanana->getActive() )
            {
                rotateAround( followBanana->getPos(), - relativeY * mRotationSpeed, vec3( 1,0,0 ) );
                rotateAround( followBanana->getPos(), relativeX * mRotationSpeed, vec3( 1,0,0 ) );
            }
        }
    }

}

void CameraControl::wheelEvent(QWheelEvent *pWheelEvent)
{
}

float oldAngle;
void CameraControl::update(float _elapsedTime)
{
    if ( !follow )
    {
        if (key[0])
            mpCamera->setPosition( arrayAdd( mpCamera->getPosition(), arrayMult( mpCamera->getDirection(), _elapsedTime * mWalkSpeed ) ) );

        if (key[1])
            mpCamera->setPosition( arrayAdd( mpCamera->getPosition(), arrayMult( mpCamera->getDirection(), - _elapsedTime * mWalkSpeed ) ) );

        if (key[2])
            mpCamera->setPosition( arrayAdd( mpCamera->getPosition(), arrayMult( mpCamera->getRight(), - _elapsedTime * mWalkSpeed ) ) );

        if (key[3])
            mpCamera->setPosition(arrayAdd(mpCamera->getPosition(), arrayMult( mpCamera->getRight(), _elapsedTime * mWalkSpeed)));
    }
    else
    {
        if ( followBanana->getActive() )
        {

            vec3 camPos = followBanana->getPos() - vec3( followBanana->getVelocity().x, 0, followBanana->getVelocity().z ).normalize() * 2.f;

            mpCamera->setPosition( camPos );

            float angle = 15.f * _elapsedTime * (0.5f - camPos.y / mpControl->getActiveGorilla()->getPos().y );

            oldAngle += angle;

            if (oldAngle < 0.f)
            {
                oldAngle = 0.f;
                angle = 0.f;
            }

            rotateAround( followBanana->getPos(), angle , vec3( 1,0,0 ) );


        }
        else
        {
            followBanana = NULL;
            follow = false;
        }
    }

}

void CameraControl::rotateCamX(float angle)
{
    mpCamera->setDirection( rotateX( mpCamera->getDirection(), angle ) );
    mpCamera->setUp( rotateX( mpCamera->getUp(), angle ) );
    mpCamera->setRight( rotateX( mpCamera->getRight(), angle ) );
}

void CameraControl::rotateCamY(float angle)
{
    mpCamera->setDirection( rotateY( mpCamera->getDirection(), angle ) );
    mpCamera->setUp( rotateY( mpCamera->getUp(), angle ) );
    mpCamera->setRight( rotateY( mpCamera->getRight(), angle ) );
}

void CameraControl::rotateAround( vec3 _p, float _deg, vec3 _axis )
{

    mpCamera->setPitch( mpCamera->getPitch() + _deg * _axis.x);
    mpCamera->setYaw( mpCamera->getYaw() + _deg * _axis.y);
    mpCamera->setRoll( mpCamera->getRoll() + _deg * _axis.z);

    vec3 v = mpCamera->getPosition() - _p;
    mat4 rx = rotationMatrixX( mpCamera->getPitch() );
    mat4 ry = rotationMatrixY( mpCamera->getYaw() );
    mat4 rz = rotationMatrixZ( mpCamera->getRoll() );

    mat4 r = mat4Mat4( ry, mat4Mat4( rx, rz ) );

    vec3 vv = mat4Vec3( r, vec3(0,0,1) );

    v = v.length() * vv + _p;

    mpCamera->setPosition( v );


}

void CameraControl::camFollow(Banana *b)
{
    if ( b->getActive() )
    {
        oldAngle = mpControl->getActiveGorilla()->getPitch();
        follow = true;
        followBanana = b;
    }
}


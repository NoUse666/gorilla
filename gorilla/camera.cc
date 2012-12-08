#include "camera.hh"
#include "functions.hh"
#include <iostream>

using namespace func;

Camera::Camera()
{
    mPosition = vec3( 0, .5f, 1.f );

    mDirection = vec3( 0, 0, -1.f );

    mRight = vec3( 1.f, 0.f, 0.f );

    mUp = vec3( 0.f, 1.f, 0.f );

    mYaw = 0;
    mPitch = 0;
    mRoll = 0;
}

void Camera::setYaw(float y)
{
    mYaw = y;
    updateLocalSystemByOrientation();

}

void Camera::setPitch(float p)
{
    mPitch = p;
    updateLocalSystemByOrientation();
}

void Camera::setRoll(float r)
{
    mRoll = r;
    updateLocalSystemByOrientation();
}

void Camera::lookAt( const vec3 &v )
{
    mDirection  = v - mPosition;
    mDirection  = mDirection.normalize();
    mRight      = crossProduct( mDirection, mUp);
    mRight      = mRight.normalize();
    mUp         = crossProduct( mRight,   mDirection);
    mUp         = mUp.normalize();

    if (mUp.x > 1.0f )
    {
        mYaw = atan2(mDirection.x*M_PI/180.f, -mDirection.z*M_PI/180.f) * 180.f/M_PI;
        mPitch = 90.0f;
        mRoll  =  0.0f;
        return;
    }
    if (mUp.x < - 1.0f)
    {
        mYaw = atan2(mDirection.x*M_PI/180.f, -mDirection.z*M_PI/180.f) * 180.f/M_PI;
        mPitch = -90.0f;
        mRoll  =   0.0f;
        return;
    }

    mYaw   = atan2(-mRight.z*M_PI/180.f,   mRight.x*M_PI/180.f) * 180.f/M_PI;
    mPitch = atan2( mDirection.y*M_PI/180.f, mUp.y*M_PI/180.f) * 180.f/M_PI;
    //mRoll  = asin(  mRight.y*M_PI/180.f) * 180.f/M_PI;
    mRoll = 0;
    //updateLocalSystemByOrientation();
}

void Camera::updateLocalSystemByOrientation()
{
    mat4 rx = rotationMatrixX( mPitch );
    mat4 ry = rotationMatrixY( mYaw );
    mat4 rz = rotationMatrixZ( mRoll );

    mat4 rotation = mat4Mat4( ry, mat4Mat4( rx, rz ) );

    vec3 r = vec3( 1.f,0.f,0.f );
    vec3 u = vec3( 0.f,1.f,0.f );
    vec3 d = vec3( 0.f, 0.f, -1.f );

    mRight = mat4Vec3( rotation, r );
    mUp = mat4Vec3( rotation, u );
    mDirection = mat4Vec3( rotation, d );

}

#ifndef CAMERA_HH
#define CAMERA_HH

#include "includes.hh"
#include "structs.hh"

class Camera
{
public:
    Camera();

    inline void setPosition(vec3 p) { mPosition = p; }
    inline void setDirection(vec3 p) { mDirection = p; }
    inline void setRight(vec3 p) { mRight = p; }
    inline void setUp(vec3 p) { mUp = p; }
    void setYaw(float y);
    void setPitch(float p);
    void setRoll(float r);
    inline vec3 getPosition() { return mPosition; }
    inline vec3 getRight() { return mRight; }
    inline vec3 getDirection() { return mDirection; }
    inline vec3 getUp() { return mUp; }
    inline float getYaw() { return mYaw; }
    inline float getPitch() { return mPitch; }
    inline float getRoll() { return mRoll; }

    void lookAt( const vec3 &v );

    void updateLocalSystemByOrientation();

private:

    vec3 mPosition;
    vec3 mDirection;
    vec3 mRight;
    vec3 mUp;
    float mYaw;
    float mPitch;
    float mRoll;

};

#endif // CAMERA_HH

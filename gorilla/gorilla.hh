#ifndef GORILLA_HH
#define GORILLA_HH

#include "includes.hh"
#include "structs.hh"
#include "camera.hh"

class Camera;

class Gorilla
{
public:
    Gorilla();

    void draw();

    inline void setPos (vec3 p) { pos = p; }
    inline vec3 getPos () { return pos; }
    inline vec3 getDirection() { return look; }
    void setColor (float r, float g, float b);

    void setAim( float _yaw, float _pitch );
    void setStrength( float _strength ) {
        strength = _strength;
        if ( strength > 1.0f ) strength = 1.0f;
        if ( strength < 0.01f ) strength = 0.01f;
    }

    void die() { alive = false; }

    bool isAlive() { return alive; }
    void setActive( bool _active ) { active = _active; }
    bool isActive() { return active; }

    void hit( const float _hit )
    {
        life -= _hit;
        if ( life <= 0.f )
        {
            life = 0.f;
            die();
        }
    }

    float getYaw();
    float getPitch();
    float getStrength() { return strength; }

    void moveCameraTo(Camera *cc);

private:

    void drawBody();
    void drawLegs();
    void drawArms();
    void drawHead();
    void drawAim();
    void drawLifeBar();

    vec3 pos;
    vec3 look;
    vec3 up;
    vec3 right;
    vec3 color;
    float yaw;
    float pitch;
    float life;
    float strength;
    bool alive;
    bool active;
    mat4 rotation, rx, ry;

};

#endif // GORILLA_HH

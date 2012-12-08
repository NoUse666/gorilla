#ifndef BANANA_HH
#define BANANA_HH

#include "includes.hh"
#include "structs.hh"
#include "functions.hh"

class Banana
{
public:
    Banana(vec3 _v0, vec3 _pos, float _phi, float _damage, float _radius);

    void draw();

    void setVelocity( vec3 _v ) { v0 = _v; }
    void setPos( vec3 _v ) { pos = _v; }
    void setPosStart( vec3 _v ) { posStart = _v; }
    void setPhi(  float _phi ) { phi = _phi; }
    void setDamage( float _damage ) { damage = _damage; }
    void setRadius( float _radius ) { radius = _radius; }
    void setTime( float _time ) { time = _time; }
    void setActive( bool _active ) { active = _active; }

    vec3 getPos() { return pos; }
    vec3 getPosStart() { return posStart; }
    vec3 getVelocity() { return v0; }
    float getPhi() { return phi; }
    float getDamage() { return damage; }
    float getRadius() { return radius; }
    float getTime() { return time; }
    float getActive() { return active; }


private:
    vec3 v0;
    vec3 pos;
    vec3 posStart;
    float time;
    float phi;
    float damage;
    float radius;
    bool active;
};

#endif // BANANA_HH

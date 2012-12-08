#ifndef STRUCTS_HH
#define STRUCTS_HH

#include <math.h>
#include "includes.hh"

struct position {
    float x;
    float y;
};

struct vec3 {
    vec3( float _x=0, float _y=0, float _z=0)
    {
        x = _x; y = _y; z = _z;
    }

    friend vec3 operator + ( const vec3 &l, const vec3 &r )
    {
        vec3 result;
        result.x = l.x + r.x;
        result.y = l.y + r.y;
        result.z = l.z + r.z;
        return result;
    }

    friend vec3 operator * ( const vec3 &v, const float &p )
    {
        return vec3(p*v.x, p*v.y, p*v.z);
    }

    friend vec3 operator * ( const float &p, const vec3 &v )
    {
        return vec3(p*v.x, p*v.y, p*v.z);
    }

    friend vec3 operator / ( const vec3 &v, const float &p )
    {
        return vec3(v.x/p, v.y/p, v.z/p);
    }

    friend vec3 operator - ( const vec3 &v )
    {
        return v*-1.f;
    }

    friend float operator * ( const vec3 &l, const vec3 &r )
    {
        return l.x*r.x + l.y*r.y + l.z*r.z;
    }

    friend vec3 operator - ( const vec3 &l, const vec3 &r )
    {
        return vec3( l.x-r.x, l.y-r.y, l.z-r.z );
    }

    float length ()
    {
        return sqrt(x*x + y*y + z*z);
    }

    vec3 normalize()
    {
        vec3 *v = this;
        return *v / v->length();
    }

    float x;
    float y;
    float z;
};

struct mat4 {
    float m[4][4];

    mat4() {
        m[0][0]=1; m[0][1]=0; m[0][2]=0; m[0][3]=0;
        m[1][0]=0; m[1][1]=1; m[1][2]=0; m[1][3]=0;
        m[2][0]=0; m[2][1]=0; m[2][2]=1; m[2][3]=0;
        m[3][0]=0; m[3][1]=0; m[3][2]=0; m[3][3]=1;
    }
};

struct quad {
    vec3 p[4];
    vec3 normal;
};


#endif // STRUCTS_HH

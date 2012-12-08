#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "structs.hh"
#include "includes.hh"

namespace func
{

    inline mat4 mat4Mat4(const mat4 &m1, const mat4 &m2)
    {
        mat4 m;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                m.m[i][j] = 0;
                for (int k=0; k<4; k++)
                    m.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
        return m;
    }

    inline vec3 mat4Vec3(const mat4 &m, const vec3 &v)
    {
        vec3 r;
        r.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
        r.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
        r.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
        return r;
    }

    inline vec3 arrayMult(const vec3 &v, float f)
    {
        vec3 w;
        w.x = v.x * f;
        w.y = v.y * f;
        w.z = v.z * f;
        return w;
    }

    inline vec3 arrayAdd(const vec3 &v, const vec3 &w)
    {
        vec3 u;
        u.x = v.x + w.x;
        u.y = v.y + w.y;
        u.z = v.z + w.z;
        return u;
    }

    inline float length( vec3 v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    inline vec3 crossProduct( vec3 a,  vec3 b)
    {
         vec3 res;

        res.x = a.y*b.z - a.z*b.y;
        res.y = a.z*b.x - a.x*b.z;
        res.z = a.x*b.y - a.y*b.x;

        return res;
    }

    inline vec3 normalize( vec3 v)
    {
        return arrayMult(v, 1.f/length( v ) );
    }

    inline float dot ( vec3 a,  vec3 b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    inline vec3 rotateX(const vec3 &v, float angle)
    {
        vec3 w = v;
        float a = angle * M_PI/180;

        w.y = v.y * cos(a) + v.z * -sin(a);
        w.z = v.y * sin(a) + v.z * cos(a);

        return w;
    }

    inline vec3 rotateY(const vec3 &v, float angle)
    {
        vec3 w = v;
        float a = angle * M_PI/180;

        w.x = v.x * cos(a) + v.z * -sin(a);
        w.z = v.x * sin(a) + v.z * cos(a);

        return w;
    }

    inline mat4 rotationMatrixX( float _degree )
    {
        mat4 tmp;
        float degree = _degree * M_PI/180.f;
        tmp.m[0][0] = 1.0f;   tmp.m[1][0] = 0.f;    tmp.m[2][0] = 0.f;    tmp.m[3][0] = 0.f;
        tmp.m[0][1] = 0.f;    tmp.m[1][1] = cos(degree);    tmp.m[2][1] = sin(degree);    tmp.m[3][1] = 0.f;
        tmp.m[0][2] = 0.f;    tmp.m[1][2] = -sin(degree);    tmp.m[2][2] = cos(degree);    tmp.m[3][2] = 0.f;
        tmp.m[0][3] = 0.f;    tmp.m[1][3] = 0.f;    tmp.m[2][3] = 0.f;    tmp.m[3][3] = 1.f;
        return tmp;
    }

    inline mat4 rotationMatrixY( float _degree )
    {
        mat4 tmp;
        float degree = _degree * M_PI/180.f;
        tmp.m[0][0] = cos(degree);   tmp.m[1][0] = 0.f;    tmp.m[2][0] = sin(degree);    tmp.m[3][0] = 0.f;
        tmp.m[0][1] = 0.f;   tmp.m[1][1] = 1.f;    tmp.m[2][1] = 0.f;    tmp.m[3][1] = 0.f;
        tmp.m[0][2] = -sin(degree);   tmp.m[1][2] = 0.f;    tmp.m[2][2] = cos(degree);    tmp.m[3][2] = 0.f;
        tmp.m[0][3] = 0.f;    tmp.m[1][3] = 0.f;    tmp.m[2][3] = 0.f;    tmp.m[3][3] = 1.f;
        return tmp;
    }

    inline mat4 rotationMatrixZ( float _degree )
    {
        mat4 tmp;
        float degree = _degree * M_PI/180.f;
        tmp.m[0][0] = cos(degree);   tmp.m[1][0] = sin(degree);    tmp.m[2][0] = 0.f;    tmp.m[3][0] = 0.f;
        tmp.m[0][1] = -sin(degree);   tmp.m[1][1] = cos(degree);    tmp.m[2][1] = 0.f;    tmp.m[3][1] = 0.f;
        tmp.m[0][2] = 0.f;   tmp.m[1][2] = 0.f;    tmp.m[2][2] = 1.f;    tmp.m[3][2] = 0.f;
        tmp.m[0][3] = 0.f;    tmp.m[1][3] = 0.f;    tmp.m[2][3] = 0.f;    tmp.m[3][3] = 1.f;
        return tmp;
    }

    inline mat4 buildFrustum( float phiInDegree, float aspectRatio, float near, float far)
    {

        mat4 frustum;

        float t = near * tan(phiInDegree * M_PI/360);
        float b = -t;
        float r = aspectRatio * t;
        float l = -r;

        frustum.m[0][0] = 2*near / (r-l);
        frustum.m[1][1] = 2*near / (t-b);
        frustum.m[2][0] = (r+l) / (r-l);
        frustum.m[2][1] = (t+b) / (t-b);
        frustum.m[2][2] = - (far+near) / (far-near);
        frustum.m[2][3] = -1;
        frustum.m[3][2] = - 2*far*near / (far-near);
        frustum.m[3][3] = 0;

        return frustum;
    }

    inline mat4 lookAt(const vec3 &camPos, const vec3 &viewDirection, const vec3 &up) {

        mat4 lookat;
        vec3 right;

        right = crossProduct( viewDirection, up );
        vec3 upNorm = crossProduct( right, viewDirection );

        vec3 viewNorm = normalize( viewDirection );
        right = normalize( right );
        upNorm = normalize( upNorm );

        lookat.m[0][0] = right.x;
        lookat.m[1][0] = right.y;
        lookat.m[2][0] = right.z;
        lookat.m[3][0] = dot( arrayMult( right, -1.f), camPos );
        lookat.m[0][1] = upNorm.x;
        lookat.m[1][1] = upNorm.y;
        lookat.m[2][1] = upNorm.z;
        lookat.m[3][1] = dot( arrayMult( upNorm, -1.f), camPos );
        lookat.m[0][2] = -viewNorm.x;
        lookat.m[1][2] = -viewNorm.y;
        lookat.m[2][2] = -viewNorm.z;
        lookat.m[3][2] = dot( viewNorm, camPos );

        return lookat;
    }

    inline void drawCube( float w, float h, float d, vec3 t , vec3 ta, vec3 pos, mat4 rotation)
    {

        vec3 p1 = pos + ta + mat4Vec3( rotation, t + vec3( 0.5f*w, 0.5f*h, 0.5f*d ) );
        vec3 p2 = pos + ta + mat4Vec3( rotation, t + vec3( -0.5f*w, 0.5f*h, 0.5f*d ) );
        vec3 p3 = pos + ta + mat4Vec3( rotation, t + vec3( -0.5f*w, -0.5f*h, 0.5f*d ) );
        vec3 p4 = pos + ta + mat4Vec3( rotation, t + vec3( 0.5f*w, -0.5f*h, 0.5f*d ) );
        vec3 p5 = pos + ta + mat4Vec3( rotation, t + vec3( 0.5f*w, 0.5f*h, -0.5f*d ) );
        vec3 p6 = pos + ta + mat4Vec3( rotation, t + vec3( -0.5f*w, 0.5f*h, -0.5f*d ) );
        vec3 p7 = pos + ta + mat4Vec3( rotation, t + vec3( -0.5f*w, -0.5f*h, -0.5f*d ) );
        vec3 p8 = pos + ta + mat4Vec3( rotation, t + vec3( 0.5f*w, -0.5f*h, -0.5f*d ) );

        glVertex3f( p1.x, p1.y, p1.z );
        glVertex3f( p2.x, p2.y, p2.z );
        glVertex3f( p3.x, p3.y, p3.z );
        glVertex3f( p4.x, p4.y, p4.z );

        glVertex3f( p5.x, p5.y, p5.z );
        glVertex3f( p6.x, p6.y, p6.z );
        glVertex3f( p7.x, p7.y, p7.z );
        glVertex3f( p8.x, p8.y, p8.z );

        glVertex3f( p1.x, p1.y, p1.z );
        glVertex3f( p5.x, p5.y, p5.z );
        glVertex3f( p6.x, p6.y, p6.z );
        glVertex3f( p2.x, p2.y, p2.z );

        glVertex3f( p8.x, p8.y, p8.z );
        glVertex3f( p7.x, p7.y, p7.z );
        glVertex3f( p3.x, p3.y, p3.z );
        glVertex3f( p4.x, p4.y, p4.z );

        glVertex3f( p1.x, p1.y, p1.z );
        glVertex3f( p5.x, p5.y, p5.z );
        glVertex3f( p8.x, p8.y, p8.z );
        glVertex3f( p4.x, p4.y, p4.z );

        glVertex3f( p2.x, p2.y, p2.z );
        glVertex3f( p6.x, p6.y, p6.z );
        glVertex3f( p7.x, p7.y, p7.z );
        glVertex3f( p3.x, p3.y, p3.z );
    }

    inline string readFromFile( string _fileName )
    {
        string
        return "";
    }
}

class Functions
{
public:
    Functions();

    static vec3 arrayMult(const vec3 &v, float f);
    static vec3 arrayAdd(const vec3 &v,const vec3 &w);
    static float length(vec3 v);
    static vec3 crossProduct(vec3 a, vec3 b);
    static vec3 normalize(vec3 v);
    static float dot(vec3 a, vec3 b);
    static vec3 rotateX(const vec3 &v, float angle);
    static vec3 rotateY(const vec3 &v, float angle);
    static mat4 buildFrustum(float phiInDegree, float aspectRatio, float near, float far);
    static mat4 lookAt(const vec3 &camPos, const vec3 &viewDirection, const vec3 &up);
    static void drawCube( float w, float h, float d, vec3 t , vec3 ta, vec3 pos, mat4 rotation);

};

#endif // FUNCTIONS_HH

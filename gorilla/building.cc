#include "building.hh"
#include "functions.hh"
#include "GL/glew.h"
#include <iostream>

using namespace func;
using namespace std;

Building::Building()
{
}

Building *Building::getBuilding(float w, float h, float d, vec3 p, vec3 c)
{
    Building *b = new Building();
    quad *q;

    b->color = c;
    b->height = h;

    vec3 v1, v2, v3, v4, v5, v6, v7, v8;

    v1.x=w/2; v1.y=0.f; v1.z=d/2;   //vru
    v2.x=-w/2; v2.y=0.f; v2.z=d/2;  //vlu
    v3.x=w/2; v3.y=0.f; v3.z=-d/2;  //hru
    v4.x=-w/2; v4.y=0.f; v4.z=-d/2; //hlu
    v5.x=w/2; v5.y=h; v5.z=d/2;     //vro
    v6.x=-w/2; v6.y=h; v6.z=d/2;    //vlo
    v7.x=w/2; v7.y=h; v7.z=-d/2;    //hro
    v8.x=-w/2; v8.y=h; v8.z=-d/2;   //hlo

    v1 = arrayAdd( v1, p );
    v2 = arrayAdd( v2, p );
    v3 = arrayAdd( v3, p );
    v4 = arrayAdd( v4, p );
    v5 = arrayAdd( v5, p );
    v6 = arrayAdd( v6, p );
    v7 = arrayAdd( v7, p );
    v8 = arrayAdd( v8, p );

    /*q = new quad();
    q->p[0] = v1; q->p[1] = v2; q->p[2] = v4; q->p[3] = v3; q->normal=vec3(0,-1,0); //unten
    b->points->push_back(q);*/
    q = new quad();
    q->p[0] = v5; q->p[1] = v6; q->p[2] = v8; q->p[3] = v7; q->normal=crossProduct( (v6-v5), (v8-v6) ).normalize(); //oben
    b->points.push_back(q);
    q = new quad();
    q->p[0] = v1; q->p[1] = v2; q->p[2] = v6; q->p[3] = v5; q->normal=crossProduct( (v1-v2), (v6-v2) ).normalize(); //vorne
    b->points.push_back(q);
    q = new quad();
    q->p[0] = v7; q->p[1] = v8; q->p[2] = v4; q->p[3] = v3; q->normal=crossProduct( (v4-v3), (v7-v3) ).normalize(); //hinten
    b->points.push_back(q);
    q = new quad();
    q->p[0] = v1; q->p[1] = v3; q->p[2] = v7; q->p[3] = v5; q->normal=crossProduct( (v3-v1), (v5-v1) ).normalize(); //rechts
    b->points.push_back(q);
    q = new quad();
    q->p[0] = v4; q->p[1] = v2; q->p[2] = v6; q->p[3] = v8; q->normal=crossProduct( (v2-v4), (v8-v4) ).normalize(); //links
    b->points.push_back(q);

    b->pos = p;

    return b;
}

bool Building::collide(Building *b)
{
    quad *q1, *q2;
    q1 = (quad*)*points.begin();

    q2 = (quad*)*b->getPoints().begin();

    for ( int i=0; i<4; i++ )
    {
        float x1, x2, x3, x4;
        vec3 v = q1->p[i] - q1->p[(i+1)%4];
        x1 = q1->p[0]*v/v.length();
        x2 = x1;
        for ( int j = 1; j<4; j++ )
        {
            float x = q1->p[j]*v/v.length();
            if ( x < x1 )
                x1 = x;
            if (x > x2)
                x2 = x;
        }

        x3 = q2->p[0]*v/v.length();
        x4 = x3;
        for ( int j = 1; j<4; j++ )
        {
            float x = q2->p[j]*v/v.length();
            if ( x < x3 )
                x3 = x;
            if (x > x4)
                x4 = x;
        }

        if ( x2 < x3 || x1 > x4 )
            return false;
    }

    for ( int i=0; i<4; i++ )
    {
        float x1, x2, x3, x4;
        vec3 v = q2->p[i] - q2->p[(i+1)%4];
        x1 = q1->p[0]*v/v.length();
        x2 = x1;
        for ( int j = 1; j<4; j++ )
        {
            float x = q1->p[j]*v/v.length();
            if ( x < x1 )
                x1 = x;
            if (x > x2)
                x2 = x;
        }

        x3 = q2->p[0]*v/v.length();
        x4 = x3;
        for ( int j = 1; j<4; j++ )
        {
            float x = q2->p[j]*v/v.length();
            if ( x < x3 )
                x3 = x;
            if (x > x4)
                x4 = x;
        }
        if ( x2 < x3 || x1 > x4 )
            return false;
    }
    return true;

}

void Building::draw()
{
    glColor3f( color.x, color.y, color.z );
    //glTranslatef(-pos.x, -pos.y, -pos.z);
    glBegin(GL_QUADS);
    for (vector<quad*>::iterator it = points.begin(); it < points.end(); it++)
    {
        quad *v = (quad*)*it;

        glNormal3f( v->normal.x, v->normal.y, v->normal.z );

        for (int i=0; i<4; i++)
            glVertex3f( v->p[i].x, v->p[i].y, v->p[i].z );

    }
    //glTranslatef(pos.x, pos.y, pos.z);
    glEnd();
}

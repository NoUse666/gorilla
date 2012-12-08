#include "banana.hh"
#include "functions.hh"

using namespace func;

Banana::Banana( vec3 _v0 = vec3(), vec3 _pos = vec3(), float _phi = 45.f, float _damage = 100.f, float _radius = 1.0f):
    v0(_v0),
    pos(_pos),
    posStart(_pos),
    phi(_phi),
    damage(_damage),
    radius(_radius),
    active( true )
{
}

void Banana::draw()
{
    glColor3f( 1.0f, 1.0f, 0.f );
    glBegin( GL_QUADS );
    drawCube( 0.04f, 0.06f, 0.04f, vec3(), vec3(), pos, mat4() );
    glEnd();
}

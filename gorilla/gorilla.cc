#include "gorilla.hh"
#include "functions.hh"
#include <iostream>

using namespace func;

Gorilla::Gorilla():
    life(100),
    alive(true),
    active(false),
    strength(0.3f),
    yaw(0),
    pitch(0),
    up(vec3(0,1,0)),
    look(vec3(0,0,-1)),
    right(vec3(1,0,0))
{
    setAim(0,0);
}

void Gorilla::draw()
{
    glColor3f(color.x, color.y, color.z);

    glBegin(GL_QUADS);

    drawBody();
    drawLegs();
    drawArms();
    drawHead();

    if (active)
        drawAim();

    drawLifeBar();

    glEnd();


}

void Gorilla::setColor(float r, float g, float b)
{
    color = vec3(r,g,b);
}

void Gorilla::setAim( float _yaw, float _pitch )
{
    pitch = _pitch;
    yaw = _yaw;

    if (pitch<-90) pitch = -90;
    if (pitch>90) pitch = 90;

    rx = rotationMatrixX( pitch );
    ry = rotationMatrixY( yaw );

    rotation = mat4Mat4( ry, rx );

    vec3 r = vec3( 1.f, 0.f, 0.f );
    vec3 u = vec3( 0.f, 1.f, 0.f );
    vec3 d = vec3( 0.f, 0.f, -1.f );

    right = mat4Vec3( rotation, r );
    up = mat4Vec3( rotation, u );
    look = mat4Vec3( rotation, d );

}

float Gorilla::getYaw()
{
    return yaw;
}

float Gorilla::getPitch()
{
    return pitch;
}


void Gorilla::moveCameraTo( Camera *cc )
{
    vec3 p = look;
    cc->setPosition( pos + vec3(0,0.75f,0) - (vec3(look.x,0,look.z).normalize()) * 1.5f );
    //cc->setDirection( -look * vec3(1,0,1) + pos * vec3(0,1,0) );
    cc->setUp( vec3(0,1,0) );
    cc->setPitch( 0 );
    cc->setYaw( yaw );
    //cc->lookAt( look * vec3(1,0,1) + pos * vec3(0,1,0) );
}

void Gorilla::drawBody()
{
    drawCube( 0.15f, 0.2f, 0.1f, vec3( 0,0.2f,0), vec3(), pos, ry  );
}

void Gorilla::drawLegs()
{
    drawCube( 0.04f, 0.1f, 0.04f, vec3( 0.05f, 0.05f, 0 ), vec3(), pos, ry );
    drawCube( 0.04f, 0.1f, 0.04f, vec3( -0.05f, 0.05f, 0 ), vec3(), pos, ry );
}

void Gorilla::drawArms()
{

    drawCube( 0.15f, 0.04f, 0.04f, vec3( 0.15f, 0.26f, 0 ), vec3(), pos, ry  );
    drawCube( 0.15f, 0.04f, 0.04f, vec3( -0.15f, 0.26f, 0 ), vec3(), pos, ry  );
}

void Gorilla::drawHead()
{
    drawCube( 0.06f, 0.06f, 0.06f, vec3( 0, 0.35f, 0 ), vec3(), pos, ry  );
}

void Gorilla::drawAim()
{
    glColor3f( 1.0f, 0.f, 0.f );
    drawCube( 0.019f, 0.019f, .49f, vec3( 0, 0, -.1f - .26f ), vec3( 0, 0.35f, 0 ), pos, rotation );
    glColor3f( 0.f,0.f, 0.8f );
    drawCube( 0.02f, 0.02f, .5f * strength, vec3( 0, 0, -.1f - .25f * strength ), vec3( 0, 0.35f, 0 ), pos, rotation );

}

void Gorilla::drawLifeBar()
{
    glColor3f( 0.f, 1.f, 0.f );
    drawCube( 0.6f * life/100.f, 0.02f, 0.02f, vec3( 0, 0.5f, 0 ), vec3(), pos, ry );
}



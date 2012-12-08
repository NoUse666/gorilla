#include "physiccontrol.hh"
#include <iostream>

PhysicControl::PhysicControl():
    wind(vec3())
{
    newWind();
}

void PhysicControl::update(float _elapsedTime)
{
    vector<vector<Banana*>::iterator> del;
    for (vector<Banana*>::iterator it = bananas.begin(); it < bananas.end(); it++ )
    {
        Banana *b = (Banana*)*it;
        vec3 v = b->getVelocity();
        float phi = b->getPhi();
        b->setTime( b->getTime() + _elapsedTime );
        v.x = v.x * b->getTime() * cos( phi * M_PI / 180.f ) + b->getTime() * b->getTime() * wind.x/2.f ;
        v.y = v.y * b->getTime() * sin( phi * M_PI / 180.f ) - b->getTime() * b->getTime() * 9.81f/2.f;
        v.z = v.z * b->getTime() * cos( phi * M_PI / 180.f ) + b->getTime() * b->getTime() * wind.z/2.f ;

        vec3 pos = b->getPosStart() + v;

        bool explode = checkCollision( b, pos );

        if (explode)
            del.push_back(it);
        else
            b->setPos( pos );
    }

    vector<vector<Gorilla*>::iterator> delGorilla;

    while ( !del.empty() )
    {
        vector<Banana*>::iterator it = del.back();
        Banana* b = (Banana*)*it;
        b->setActive( false );

        for ( vector<Gorilla*>::iterator git = gorillas.begin(); git < gorillas.end(); git++ )
        {
            Gorilla *g = (Gorilla*)*git;
            float d = (g->getPos() - b->getPos()).length();
            if ( d < b->getRadius() )
            {
                g->hit( b->getDamage() * ( 1.f - fabs( d ) / b->getRadius() ) );
                if ( !g->isAlive() )
                {
                    if ( g->isActive() )
                        nextGorilla();
                    delGorilla.push_back(git);
                }
            }
        }

        bananas.erase( it );
        del.pop_back();
    }

    while ( !delGorilla.empty() )
    {
        vector<Gorilla*>::iterator it = delGorilla.back();
        gorillas.erase( it );
        delGorilla.pop_back();
    }

}

void PhysicControl::addBanana(Banana *_b)
{
    bananas.push_back( _b );
}

void PhysicControl::addBuilding(Building *_b)
{
    buildings.push_back( _b );
}

void PhysicControl::addGorilla(Gorilla *_g)
{
    gorillas.push_back( _g );
}

void PhysicControl::newWind()
{
    float x, z;

    x = (float)(rand()%1000)/200 - 2.5f ;
    z = (float)(rand()%1000)/200 - 2.5f ;
    wind.x = x;
    wind.z = z;

    std::cout << "wind: " << wind.x << " " << wind.z << std::endl;
}

void PhysicControl::nextGorilla()
{
    if ( !gorillas.empty() )
    {
        bool active = false;

        vector<Gorilla*>::iterator next;

        for ( vector<Gorilla*>::iterator it = gorillas.begin(); it < gorillas.end(); it++ )
        {
            Gorilla *g = (Gorilla*)*it;

            if ( active )
            {
                active = false;
                g->setActive( true );
                it = gorillas.end();
            }
            else
            {
                active = g->isActive();
                g->setActive( false );
            }
        }

        if ( active )
        {
            Gorilla *g = (Gorilla*)*gorillas.begin();
            g->setActive( true );

        }
    }
    newWind();

}

bool PhysicControl::checkCollision( Banana *b, vec3 pos )
{

    float radius = 0.1f;

    if ( pos.y<=0 )
        return true;

    for ( vector<Building*>::iterator it = buildings.begin(); it < buildings.end(); it++ )
    {
        Building *building = (Building*)*it;
        vector<quad*> quads = building->getPoints();
        for ( vector<quad*>::iterator qit = quads.begin(); qit < quads.end(); qit++ )
        {
            quad *q = (quad*)*qit;
            float d1 = ( b->getPos() - q->p[0] ) * q->normal;
            float d2 = ( pos - q->p[0] ) * q->normal;

            int sig1 = d1<0?-1:(d1>0?1:0);
            int sig2 = d2<0?-1:(d2>0?1:0);

            if ( fabs( d1 ) <= radius || fabs( d2 ) <= radius || sig1 != sig2 )
            {

                vec3 ray = ( pos - b->getPos() ).normalize();
                float d = d1 / ( ray * - q->normal );
                vec3 i = pos + ray * d;

                float xmin = q->p[0].x, ymin = q->p[0].y, zmin = q->p[0].z;
                float xmax = q->p[0].x, ymax = q->p[0].y, zmax = q->p[0].z;
                for (int i=1; i<4; i++ )
                {
                    if (q->p[i].x < xmin) xmin = q->p[i].x;
                    if (q->p[i].x > xmax) xmax = q->p[i].x;
                    if (q->p[i].y < ymin) ymin = q->p[i].y;
                    if (q->p[i].y > ymax) ymax = q->p[i].y;
                    if (q->p[i].z < zmin) zmin = q->p[i].z;
                    if (q->p[i].z > zmax) zmax = q->p[i].z;
                }

                if ( ( i.x >= xmin && i.x <= xmax && i.y >= ymin && i.y <= ymax && zmax == zmin )
                     || ( i.x >= xmin && i.x <= xmax && i.z >= zmin && i.z <= zmax && ymax == ymin )
                     || ( i.z >= zmin && i.z <= zmax && i.y >= ymin && i.y <= ymax && xmax == xmin ) )
                    return true;
            }
        }
    }


    return false;
}

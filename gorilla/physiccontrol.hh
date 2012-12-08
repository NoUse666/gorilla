#ifndef PHYSICCONTROL_HH
#define PHYSICCONTROL_HH

#include "structs.hh"
#include "gorilla.hh"
#include "building.hh"
#include "banana.hh"


class PhysicControl
{
public:
    PhysicControl();

    void update( float _elapsedTime );

    void addBanana( Banana *_b );
    void addBuilding( Building *_b );
    void addGorilla( Gorilla *_g );

    void newWind();

    vector<Banana*> *getBananas() { return &bananas; }
    vector<Building*> *getBuildings() { return &buildings; }
    vector<Gorilla*> *getGorillas() { return &gorillas; }

    vec3 getWind() { return wind; }

    void nextGorilla();

private:
    bool checkCollision( Banana *b, vec3 pos );

    vector<Building*> buildings;
    vector<Gorilla*> gorillas;
    vector<Banana*> bananas;
    vec3 wind;

};

#endif // PHYSICCONTROL_HH

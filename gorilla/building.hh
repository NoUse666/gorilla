#ifndef BUILDING_HH
#define BUILDING_HH

#include "includes.hh"
#include "structs.hh"

using namespace std;

class Building
{
public:
    Building();

    static Building *getBuilding(float w, float h, float d, vec3 p, vec3 c);

    bool collide( Building *b );

    inline vector<quad*> getPoints() { return points; }
    inline vec3 getPos() { return pos; }
    inline vec3 getColor() { return color; }
    inline float getHeight() { return height; }
    void draw();

private:
    vector<quad*> points;
    vec3 pos;
    vec3 color;
    float height;
};

#endif // BUILDING_HH

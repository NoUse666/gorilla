#ifndef VAO_HH
#define VAO_HH

#include "structs.hh"
#include "GL/glew.h"

class VAO
{
public:
    VAO();

private:
    GLuint mObjectName;
    GLenum mMode;

};

#endif // VAO_HH

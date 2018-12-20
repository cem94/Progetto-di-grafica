#include "Engine.h"
// FreeGLUT:
#include <GL/freeglut.h>


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

std::vector<glm::vec4> Mesh::getVertexes() const
{
    return vertexes;
}

void Mesh::renderMesh()
{
}

glm::vec4 Mesh::getPosition() const
{
    return glm::vec4();
}

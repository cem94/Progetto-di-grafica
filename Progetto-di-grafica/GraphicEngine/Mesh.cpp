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

void Mesh::render(glm::mat4 renderMatrix)
{
}

Material * Mesh::getMaterial() const
{
	return material;
}



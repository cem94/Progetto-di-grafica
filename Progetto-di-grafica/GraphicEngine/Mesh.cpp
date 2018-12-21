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

void Mesh::setVertices(std::vector<glm::vec4> vertexes)
{
	this->vertexes = vertexes;
}

void Mesh::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
//TODO completare
}

Material * Mesh::getMaterial() const
{
	return material;
}

void Mesh::setMaterial(Material * material)
{
	this->material = material;
}



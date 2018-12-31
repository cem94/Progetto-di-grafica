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

void Mesh::setVertexes(std::vector<glm::vec4> vertexes)
{
	this->vertexes = vertexes;
}

std::vector<glm::vec4> Mesh::getNormals() const
{
	return normals;
}

void Mesh::setNormals(std::vector<glm::vec4> normals)
{
	this->normals = normals;
}

std::vector<glm::vec4> Mesh::getTextureCoordinates() const
{
	return this->textureCoordinates;
}

void Mesh::setTextureCoordinates(std::vector<glm::vec4> textureCoordinates)
{
	this->textureCoordinates = textureCoordinates;
}

Material * Mesh::getMaterial() const
{
	return material;
}

void Mesh::setMaterial(Material * material)
{
	this->material = material;
}

void Mesh::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	//TODO completare capire come si usa
}

Object::Type Mesh::getType() const
{
	return MESH;
}
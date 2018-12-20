#include "Engine.h"


// FreeGLUT:
#include <GL/freeglut.h>

Material::Material()
{
}

Material::~Material()
{
}

Texture * Material::getTexture() const
{
	return this->texture;
}



void Material::render(glm::mat4 renderMatrix)
{
	//TODO
}

void Material::setTexture(Texture * texture)
{
	this->texture = texture;
}



void Material::setAmbient(glm::vec4 ambient)
{
	this->ambient = ambient;
}

void Material::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec4 specular)
{
	this->specular = specular;
}

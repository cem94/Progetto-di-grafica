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

Object::Type Material::getType() const
{
	return MATERIAL;
}

void Material::setTexture(Texture * texture)
{
	this->texture = texture;
}



void Material::setAmbient(glm::vec4 ambient)
{
	this->ambient = ambient;
}

glm::vec4 Material::getAmbient()
{
	return this->ambient;
}

void Material::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse = diffuse;
}

glm::vec4 Material::getDiffuse()
{
	return this->diffuse;
}

void Material::setSpecular(glm::vec4 specular)
{
	this->specular = specular;
}

glm::vec4 Material::getSpecular()
{
	return this->specular;
}

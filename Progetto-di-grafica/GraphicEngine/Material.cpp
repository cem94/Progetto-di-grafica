#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

Material::Material()
{
}

Material::Material(const char * name)
{
		this->setName(name);	
}

Material::~Material()
{
}

Texture * Material::getTexture() const
{
	return this->texture;
}

void Material::setTexture(const char * textureName)
{
//TODO
}

void Material::setTexture(Texture * texture)
{
	this->texture = texture;
}

void Material::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

glm::vec3 Material::getAmbient()
{
	return this->ambient;
}

void Material::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

glm::vec3 Material::getDiffuse()
{
	return this->diffuse;
}

void Material::setSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

glm::vec3 Material::getSpecular()
{
	return this->specular;
}

Object::Type Material::getType() const
{
	return MATERIAL;
}

float Material::getShininess() const
{
	return this->shininess;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

glm::vec4 Material::getEmissive() const
{
	return this->emissive;
}

void Material::setEmissive(glm::vec4 emissive)
{
	this->emissive = emissive;
}
void Material::render(glm::mat4 renderMatrix)
{
	//TODO
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec3(ambient[0], ambient[1], ambient[2])));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec3(diffuse[0], diffuse[1], diffuse[2])));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec3(specular[0], specular[1], specular[2])));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(emissive[0], emissive[1], emissive[2])));
}

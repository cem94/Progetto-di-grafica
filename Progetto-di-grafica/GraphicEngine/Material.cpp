#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>
//TODO trasparenze
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
void Material::setTexture(const char * textureName)
{
	if (textureName != "[none]")
	{
		this->setTexture(new Texture(textureName));
	}
}
//una volte create trasparenze sostituire 1 con alpha
void Material::render(glm::mat4 renderMatrix)
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(ambient[0], ambient[1], ambient[2],1)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(diffuse[0], diffuse[1], diffuse[2],1)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(specular[0], specular[1], specular[2],1)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(emissive[0], emissive[1], emissive[2])));
}

#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

Light::Light()
{
}


Light::~Light()
{
}

short Light::getIntensity() const
{
	return this->intensity;
}

void Light::setIntensity(short intensity)
{
	this->intensity = intensity;
}

void Light::setAmbient(glm::vec4 ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec4 specular)
{
	this->specular = specular;
}
//TODO completare
void Light::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	//glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(this->ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(this->diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(this->specular));
}

void Light::typeLight()
{
}
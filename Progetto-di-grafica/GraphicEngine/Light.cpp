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
	this->intensity=intensity;
}

void Light::setAmbient(glm::vec4 ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse=diffuse;
}

void Light::setSpecular(glm::vec4 specular)
{
	this->specular = specular;
}

void Light::render(glm::mat4 renderMatrix)
{
}

void Light::typeLight()
{
}

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
    return 0;
}

void Light::setIntensity(short intensity)
{
}

void Light::renderLight()
{
}

void Light::typeLight()
{
}

glm::vec4 Light::getPosition() const
{
    return glm::vec4();
}

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
//TODO miglioorare
void Light::render(glm::mat4 renderMatrix)
{
	//set renderingMatrix as current OpenGL Matrix
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	//setto le componenti
	glLightfv(getLightNumber(), GL_AMBIENT, glm::value_ptr(this->ambient));
	glLightfv(getLightNumber(), GL_DIFFUSE, glm::value_ptr(this->diffuse));
	glLightfv(getLightNumber(), GL_SPECULAR, glm::value_ptr(this->specular));
	switch (this->subType) {
	case DIRECTIONAL:
		/////directional [ x , y  ,z , 0.0f ]/////////////////////
		glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));//dovremmo settare la posizione da un altra parte cos� da poter settare this->position sopra
		break;
	case OMNI:
		/////omnidirectional [ x , y  ,z , 1.0f ], cutoff=180 /////
		glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &angle);
		break;
	case SPOTLIGHT:
		/////spotlight [ x , y , z , 1.0f ], 0 < cutoff < 90 //////
		glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &angle);
		glLightfv(getLightNumber(), GL_SPOT_DIRECTION, glm::value_ptr(direction));
		break;
	}
}

Object::Type Light::getType() const
{
	return LIGHT;
}
Light::SubType Light::getSubType() const
{
	return this->subType;
}
//seleziona tipo luce (directional/omni/spotlight)
void Light::setSubType(Light::SubType subtype)
{
	this->subType = subType;
}
//TODO migliorare
int Light::getLightNumber()
{
	switch (this->getID())
	{
	case 0:
		return GL_LIGHT0;
		break;
	case 1:
		return GL_LIGHT1;
		break;
	case 2:
		return GL_LIGHT2;
		break;
	case 3:
		return GL_LIGHT3;
		break;
	case 4:
		return GL_LIGHT4;
		break;
	case 5:
		return GL_LIGHT5;
		break;
	case 6:
		return GL_LIGHT6;
		break;
	case 7:
		return GL_LIGHT7;
		break;
	default:
		return GL_LIGHT0;
		break;
	}
}

void Light::enableLight(bool enable)
{
	if (enable) {
		glEnable(getLightNumber());
		this->isActive = true;
	}
	else {
		glDisable(getLightNumber());
		this->isActive = false;
	}
}

void Light::setColor(glm::vec4 color)
{
	this->color = color;
	this->setAmbient(glm::vec4(color));
	this->setDiffuse(glm::vec4(color));
	this->setSpecular(glm::vec4(color));
}

void Light::setPosition(glm::vec4 position)
{
	this->position = position;
}

glm::vec3 Light::getDirection()
{
	return this->direction;
}

void Light::setDirection(glm::vec4 direction)
{
	this->direction = direction;
}

void Light::setAngle(float angle)
{
	this->angle = angle;
}
float Light::getAngle() const
{
	return this->angle;
}
float Light::getRadius() const
{
	return this->radius;
}
void Light::setRadius(float radius)
{
	this->radius = radius;
}
float Light::getCutoff() const
{
	return this->cutoff;
}
void Light::setCutoff(float cutoff)
{
	this->cutoff = cutoff;
}
//TODO rimuovere in qualche modo
void Light::setMatrix(glm::mat4 matrix)
{
	Node::setMatrix(matrix);
}

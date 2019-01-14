#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

Light::Light(){}

Light::~Light(){}

short Light::getIntensity() const{	return this->intensity;}

void Light::setIntensity(short intensity){	this->intensity = intensity;}

void Light::setAmbient(glm::vec3 ambient){	this->ambient = ambient;}

void Light::setDiffuse(glm::vec3 diffuse){	this->diffuse = diffuse;}

void Light::setSpecular(glm::vec3 specular){	this->specular = specular;}

//TODO miglioorare
void Light::render(glm::mat4 renderMatrix)
{
	printf("Rendering light \n");
	//set renderingMatrix as current OpenGL Matrix
	glLoadMatrixf(glm::value_ptr(renderMatrix));

	//setto le componenti
	glLightfv(getLightNumber(), GL_AMBIENT, glm::value_ptr(this->ambient));
	glLightfv(getLightNumber(), GL_DIFFUSE, glm::value_ptr(this->diffuse));
	glLightfv(getLightNumber(), GL_SPECULAR, glm::value_ptr(this->specular));
	
	// DIRECTIONAL
	////directional [ x , y  ,z , 0.0f ]/////////////////////
	// OMNI
    /////omnidirectional [ x , y  ,z , 1.0f ], cutoff=180 /////
	// SPOTLIGHT
    /////spotlight [ x , y , z , 1.0f ], 0 < cutoff < 90 //////

	// DIRECTIONL, OMNI AND SPOTLIGHT
	glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(this->position));
	
	// OMNI OR SPOTLIGHT
	if (this->subType != DIRECTIONAL) {

          glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &angle);

		  // ONLY SPOTLIGHT
		  if (this->subType != OMNI)
            glLightfv(getLightNumber(), GL_SPOT_DIRECTION, glm::value_ptr(direction));
	}
}

Object::Type Light::getType() const{	return LIGHT;}

Light::SubType Light::getSubType() const{	return this->subType;}

//seleziona tipo luce (directional/omni/spotlight)
void Light::setSubType(Light::SubType subtype){		this->subType = subType;}

int Light::getLightNumber()
{
	const int n_light = this->getID();
	// we have 7 light, 0 = 0x4000 and 7 = 0x4007
	if (0 <= n_light || n_light <= 7)
          return GL_LIGHT0 + n_light;
	else 
		return GL_LIGHT0;
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

void Light::setColor(glm::vec3 color)
{
	this->color = color;
	this->setAmbient(glm::vec3(color));
	this->setDiffuse(glm::vec3(color));
	this->setSpecular(glm::vec3(color));
}

void Light::setPosition(glm::vec4 position)
{
	this->position = position;
}

glm::vec3 Light::getDirection()
{
	return this->direction;
}

void Light::setDirection(glm::vec3 direction)
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
//TODO:: GERG cosa intendi? che devo rimuovere questo metodo da questa classe?
void Light::setMatrix(glm::mat4 matrix)
{
	Node::setMatrix(matrix);
}
#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>
int Light::numberOfLights = 0;

Light::Light()
{

}

Light::Light(std::string name) {
	printf("Adding light %s", name.c_str());
	printf("Number of lights %d", numberOfLights + 1);
	numberOfLights = numberOfLights + 1;
	lightNumber = numberOfLights;
	this->setName(name);
	this->setId(lightNumber);
}

Light::~Light() {}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
short Light::getIntensity() const { return this->intensity; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setIntensity(short intensity) { this->intensity = intensity; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
 //forse usare reference & per color,ambient,diffuse,specular
void Light::setAmbient(glm::vec4 ambient) { this->ambient = ambient; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setDiffuse(glm::vec4 diffuse) { this->diffuse = diffuse; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setSpecular(glm::vec4 specular) { this->specular = specular; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::changeState()
{
	if (this->isActive)
		this->disableLight();
	else
		this->enableLight();
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::render(glm::mat4 renderMatrix)
{
	//set renderingMatrix as current OpenGL Matrix
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	//setto le componenti
	glLightfv(getLightNumber(), GL_AMBIENT, glm::value_ptr(this->ambient));
	glLightfv(getLightNumber(), GL_DIFFUSE, glm::value_ptr(this->diffuse));
	glLightfv(getLightNumber(), GL_SPECULAR, glm::value_ptr(this->specular));
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

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Light::SubType Light::getSubType() const { return this->subType; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setSubType(Light::SubType subtype) { this->subType = subType; }
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int Light::getLightNumber()
{
	switch (this->getId())
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
	/*const int n_light = this->getId();
	// we have 7 light, 0 = 0x4000 and 7 = 0x4007
	if (0 <= n_light && n_light <= 7)
		return GL_LIGHT0 + n_light;
	else
		return GL_LIGHT0;*/
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setColor(glm::vec4 color)
{
	this->color = color;
	this->setAmbient(glm::vec4(color));
	this->setDiffuse(glm::vec4(color));
	this->setSpecular(glm::vec4(color));
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setPosition(glm::vec4 position)
{
	this->position = position;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::vec3 Light::getDirection()
{
	return this->direction;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setDirection(glm::vec4 direction)
{
	this->direction = direction;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setAngle(float angle)
{
	this->angle = angle;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
float Light::getAngle() const
{
	return this->angle;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
float Light::getRadius() const
{
	return this->radius;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setRadius(float radius)
{
	this->radius = radius;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
float Light::getCutoff() const
{
	return this->cutoff;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Light::setCutoff(float cutoff)
{
	this->cutoff = cutoff;
}


/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
*/
void Light::enableLight()
{
	glEnable(getLightNumber());
	this->isActive = true;
}

/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
*/
void Light::disableLight()
{
	glDisable(getLightNumber());
	this->isActive = false;
}

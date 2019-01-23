#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

int Light::numberOfLights = 0;

/**
 * Light constructor
 */
Light::Light()
{
}
/**
 * Light constructor it also set the light number
 * @param name a string containing the name of the light
 */
Light::Light(std::string name)
{
	this->setName(name);
	this->setLightNumber(numberOfLights++);
}

/**
 * Light destructor
 */
Light::~Light()
{
}

/**
 * Setter for ambient
 * @param ambient light ambient value
 */
void Light::setAmbient(glm::vec4 ambient)
{
	this->ambient = ambient;
}

/**
 * Setter for diffuse
 * @param diffuse light diffuse value
 */
void Light::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse = diffuse;
}

/**
 * Setter for specular
 * @param specular light specular value
 */
void Light::setSpecular(glm::vec4 specular)
{
	this->specular = specular;
}

/**
 * Switch that change the state of the light
 */
void Light::changeState()
{
	if (this->isActive)
		this->disableLight();
	else
		this->enableLight();
}

/**
 * Getter for light subtype
 * @return subtype value
 */
Light::Subtype Light::getSubtype() const
{
	return this->subtype;
}

/**
 * Setter for light subtype
 * @param An enum containing the light subtype
 */
void Light::setSubtype(Light::Subtype subtype)
{
	this->subtype = subtype;
}

/**
 * Getter for light number we have 7 light, 0 = 0x4000 and 7 = 0x4007
 * @return an OpenGL enum representing a light
 */
int Light::getLightNumber() const
{
	const int n_light = lightNumber;
	if (0 <= n_light && n_light <= 7)
		return GL_LIGHT0 + n_light;
	else
		return GL_LIGHT0;
}

/**
 * Setter for light number
 * @param lightNumber light number
 */
void Light::setLightNumber(int lightNumber)
{
	this->lightNumber = lightNumber;
}

/**
 * Setter for Light color
 * @param color light color
 */
void Light::setColor(glm::vec4 color)
{
	this->color = color;
	this->setAmbient(glm::vec4(color));
	this->setDiffuse(glm::vec4(color));
	this->setSpecular(glm::vec4(color));
}

/**
 * Setter for light position
 * @param position light position
 */
void Light::setPosition(glm::vec4 position)
{
	this->position = position;
}

/**
 * Getter for light direction
 * @return light direction
 */
glm::vec3 Light::getDirection()
{
	return this->direction;
}

/**
 * Setter for light direction
 * @param direction light direction
 */
void Light::setDirection(glm::vec4 direction)
{
	this->direction = direction;
}

/**
 * Getter for light angle
 * @return light angle
 */
float Light::getAngle() const
{
	return this->angle;
}

/**
 * Setter for light angle
 * @param angle light angle
 */
void Light::setAngle(float angle)
{
	this->angle = angle;
}

/**
 * Getter for light radius
 * @return light radius
 */
float Light::getRadius() const
{
	return this->radius;
}

/**
 * Setter for light radius
 * @param light radius
 */
void Light::setRadius(float radius)
{
	this->radius = radius;
}

/**
 * Getter for light cutoff
 * @return light cutoff
 */
float Light::getCutoff() const
{
	return this->cutoff;
}

/**
 * Setter for light cutoff
 * @param cutoff light cutoff
 */
void Light::setCutoff(float cutoff)
{
	this->cutoff = cutoff;
}

/**
 * Enable light
 */
void Light::enableLight()
{
	glEnable(getLightNumber());
	this->isActive = true;
}

/**
 * Disable Light
 */
void Light::disableLight()
{
	glDisable(getLightNumber());
	this->isActive = false;
}

/**
 * Render render method for light
 * @param renderMatrix light render matrix
 */
void Light::render(glm::mat4 renderMatrix)
{
	glm::vec4 ambientI = ambient * intensity;
	glm::vec4 diffuseI = diffuse * intensity;
	glm::vec4 specularI = specular * intensity;

	glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
	glLightfv(getLightNumber(), GL_SHININESS, &shininess);

	float cut = 180.0f;
	// Load light
	switch (subtype)
	{
	case OMNI:
		// for future implementation
		break;
	case SPOTLIGHT:
		glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cut);
		break;
	case DIRECTIONAL:
		glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cut);
		glLightfv(getLightNumber(), GL_SPOT_DIRECTION, glm::value_ptr(direction));
		break;
	default:
		break;
	}
	glLightfv(getLightNumber(), GL_AMBIENT, glm::value_ptr(ambientI));
	glLightfv(getLightNumber(), GL_DIFFUSE, glm::value_ptr(diffuseI));
	glLightfv(getLightNumber(), GL_SPECULAR, glm::value_ptr(specularI));
	glLightfv(getLightNumber(), GL_LINEAR_ATTENUATION, &attenuation);
}

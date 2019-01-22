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
 * @param  name a string containing the name of the light
 */
Light::Light(std::string name)
{
    this->setName(name);
    //TODO potrebbe essere un problema -> id non univoci cambiato in setLightNumber (era setId)
    this->setLightNumber(numberOfLights++);
}
/**
 * Light destructor
 */
Light::~Light() {}

////TODO:: GREG NON LO USIAMO! POSSIAMO RIMUOVERLO
///**
// * Getter for intensity
// * @return intensity light intensity
// */
//short Light::getIntensity() const
//{
//	return this->intensity;
//}
//
///**
// * Setter for intensity
// * @param  intensity light intensity
// */
//void Light::setIntensity(short intensity)
//{
//	this->intensity = intensity;
//}

/**
 * Setter for ambient
 * @param  ambient light ambient value
 */
void Light::setAmbient(glm::vec4 ambient)
{
    this->ambient = ambient;
}

/**
 * Setter for diffuse
 * @param  diffuse light diffuse value
 */
void Light::setDiffuse(glm::vec4 diffuse)
{
    this->diffuse = diffuse;
}
/**
 * Setter for specular
 * @param  specular light specular value
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
 * Render render method for light
 * @param  renderMatrix light render matrix
 */
void Light::render(glm::mat4 renderMatrix)
{
    glm::vec4 ambientI = ambient * intensity;
    glm::vec4 diffuseI = diffuse * intensity;
    glm::vec4 specularI = specular * intensity;

    Camera* camera = Engine::getInstance().getCurrentCamera();
    glLoadMatrixf(glm::value_ptr(camera->getMatrix() * renderMatrix));

    //glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(this->position));
    glLightfv(getLightNumber(), GL_POSITION, glm::value_ptr(glm::vec3(0.0f,0.0f, 0.0f)));
    glLightfv(getLightNumber(), GL_SHININESS, &shiny);

    // Load light
    switch (subtype)
    {
    case OMNI:
        break;
    case SPOTLIGHT:
        glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cutoff);
        break;
    case DIRECTIONAL:
        glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cutoff);
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
 * @param  An enum containing the light subtype
 */
void Light::setSubtype(Light::Subtype subtype)
{
    this->subtype = subtype;
}

// TODO riprovare metodo Cem
/*
 * Getter for light number
 * @return an OpenGL enum representing a light
 */
int Light::getLightNumber() const
{
    switch (lightNumber)
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

void Light::setLightNumber(int lightNumber)
{
    this->lightNumber = lightNumber;
}

/**
 * Setter for Light color
 * @param  color light color
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
 * @param  position
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
 * Setteer for light direction
 * @param  direction light direction
 */
void Light::setDirection(glm::vec4 direction)
{
    this->direction = direction;
}

/**
 * Setter for light angle
 * @param  angle light angle
 */
void Light::setAngle(float angle)
{
    this->angle = angle;
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
 * @param  cutoff light cutoff
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

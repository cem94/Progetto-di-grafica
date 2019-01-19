#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

/**
 * Material constructor
 */
Material::Material()
{
}

/**
 * Material destructor
 */
Material::~Material()
{
}

/**
 * Getter for texture
 * @return material texture
 */
Texture * Material::getTexture() const
{
	return this->texture;
}

/**
 * Setter for texture
 * @param  texture material texture
 */
void Material::setTexture(Texture * texture)
{	
	this->texture = texture;
}

/**
 * Getter for ambient
 * @return material ambient
 */
glm::vec3 Material::getAmbient()
{
	return this->ambient;
}

/**
 * Setter for ambient
 * @param  ambient material ambient
 */
void Material::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

/**
 * Getter for diffuse
 * @return material diffuse
 */
glm::vec3 Material::getDiffuse()
{
	return this->diffuse;
}

/**
 * Setter for diffuse 
 * @param  diffuse material diffuse
 */
void Material::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

/**
 * Getter for specular
 * @return material specular
 */
glm::vec3 Material::getSpecular()
{
	return this->specular;
}

/**
 * Setter for specular
 * @param  specular material specular
 */
void Material::setSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

/**
 * Getter for shininess
 * @return material shininess
 */
float Material::getShininess() const
{
	return this->shininess;
}

/**
 * Setter for shininess
 * @param  shininess material shininess
 */
void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}
/**
 * Getter for alpha
 * @return material alpha
 */
float Material::getAlpha() const
{
	return this->alpha;
}
/**
 * Setter for alpha
 * @param  alpha material alpha
 */
void Material::setAlpha(float alpha)
{
	//TODO cambiare
	if (isTrasparent())
		activeTransparencies();
	this->alpha = alpha;
}
/**
 * Getter for emissive
 * @return material emissive
 */
glm::vec4 Material::getEmissive() const
{
	return this->emissive;
}
/**
 * Setter for emissive
 * @param  emissive material emissive
 */
void Material::setEmissive(glm::vec4 emissive)
{
	this->emissive = emissive;
}

/**
 * Setter for texture it creates a new texture with the given name
 * @param  textureName name of the texture
 */
void Material::setTexture(std::string textureName)
{
	this->setTexture(new Texture(textureName));
}

/**
 * Render for material
 * @param  renderMatrix render matrix (its not used by this method)
 */
void Material::render(glm::mat4 renderMatrix)
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(ambient[0], ambient[1], ambient[2],alpha)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(diffuse[0], diffuse[1], diffuse[2],alpha)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(specular[0], specular[1], specular[2],alpha)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(emissive[0], emissive[1], emissive[2])));
}
/**
* Method that verifies if the material is transparent (alpha = 1 not transparent transparent otherwise)
*/
bool Material::isTrasparent()
{
	return this->alpha != 1;
}
/**
* Method that enables transparencies
*/
void Material::activeTransparencies()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>
//TODO trasparenze
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Material::Material(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Material::~Material(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Texture * Material::getTexture() const{	return this->texture;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setTexture(Texture * texture){	this->texture = texture;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setAmbient(glm::vec3 ambient){	this->ambient = ambient;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::vec3 Material::getAmbient(){	return this->ambient;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setDiffuse(glm::vec3 diffuse){	this->diffuse = diffuse;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::vec3 Material::getDiffuse(){	return this->diffuse;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setSpecular(glm::vec3 specular){	this->specular = specular;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::vec3 Material::getSpecular(){	return this->specular;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
float Material::getShininess() const{	return this->shininess;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setShininess(float shininess){	this->shininess = shininess;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::vec4 Material::getEmissive() const{	return this->emissive;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setEmissive(glm::vec4 emissive){	this->emissive = emissive;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Material::setTexture(std::string textureName)
{
		this->setTexture(new Texture(textureName));
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
//una volte create trasparenze sostituire 1 con alpha
void Material::render(glm::mat4 renderMatrix)
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(ambient[0], ambient[1], ambient[2],1)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(diffuse[0], diffuse[1], diffuse[2],1)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(specular[0], specular[1], specular[2],1)));
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec3(emissive[0], emissive[1], emissive[2])));
}
#include "Engine.h"
// FreeGLUT:
#include <GL/freeglut.h>

//// FreeImage:
#include <FreeImage.h>


Texture::Texture()
{
}

Texture::Texture(std::string textureName)
{
	this->setName(textureName);
	glGenTextures(1, &textureId);
	//TODO completare generazione texture
}

//libera risorse
Texture::~Texture()
{
	glDeleteTextures(1, &textureId); 
}
//renderizza la texture
void Texture::render(glm::mat4 rendermatrix)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnable(GL_TEXTURE_2D);
}

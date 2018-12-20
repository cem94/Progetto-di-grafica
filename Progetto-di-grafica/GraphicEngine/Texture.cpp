#include "Engine.h"
// FreeGLUT:
#include <GL/freeglut.h>

//// FreeImage:
//#include <FreeImage.h>


Texture::Texture()
{
}

Texture::Texture(std::string textureName)
{
	this->setName(textureName);
	//glGenTextures(1, &textureId);
	//TODO potremmo anche spostarlo in render
}


Texture::~Texture()
{
	//glDeleteTextures(1, this->getID()); TODO decidere come gestire id
}

void Texture::render(glm::mat4 rendermatrix)
{

}

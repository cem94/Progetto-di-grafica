#include "Engine.h"
// FreeGLUT:
#include <GL/freeglut.h>

//// FreeImage:
#include <FreeImage.h>


Texture::Texture()
{
}
bool exists_test1(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}
Texture::Texture(std::string textureName)
{
	this->setName(textureName);
	glGenTextures(1, &textureId);
	std::string texturePath = "../resources/";
	const char* fileName = texturePath.append(textureName).c_str();
	if (exists_test1(fileName)) {
		std::cout << "File exist!" << std::endl;
	}
	else {
		std::cout << "File not found. Current working directory: "<< workingdir().c_str() << std::endl;
	}
	//TODO completare generazione texture
	//TODO
	//FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(fileName, 0), fileName);
	/*
	int format = GL_RGB;
	GLenum extFormat = GL_BGR_EXT;

	if (FreeImage_GetBPP(bitmap) == 32)
	{
		format = GL_RGBA;
		extFormat = GL_BGRA_EXT;
	}

	// Update texture content:
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Set circular coordinates:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

	// Set min/mag filters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Using mipmapping:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, format, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), extFormat, GL_UNSIGNED_BYTE, (void *)FreeImage_GetBits(bitmap));

	// Free resources:
	FreeImage_Unload(bitmap);
	*/}

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

#include "Engine.h"

// FreeGLUT:
#include <GL/freeglut.h>

// FreeImage:
#include <FreeImage.h>

//Defines for Anisotropic filtering
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

/**
 * Texture constructor
 */
Texture::Texture()
{
}

/**
 * Texture constructor if textureName is valid it generates the corresponding texture
 * @param textureName the name of the texture
 */
Texture::Texture(std::string textureName)
{
	if (textureName.compare("[none]") == 0)
	{
		return;
	}
	this->setName(textureName);
	textureId = getId();
	glGenTextures(1, &textureId);
	std::string texturePath = "../resources/";
	const char* fileName = texturePath.append(textureName).c_str();
	//create bitmap containing our texture
	FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(fileName, 0), fileName);
	//in/out formats
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
	//check for anisotropic
	bool isAnisotropicSupported = false;
	int anisotropicLevel = 1;
	if (strstr((const char *)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
	{
		isAnisotropicSupported = true;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropicLevel);
	}
	if (isAnisotropicSupported)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
	gluBuild2DMipmaps(GL_TEXTURE_2D, format, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), extFormat, GL_UNSIGNED_BYTE, (void *)FreeImage_GetBits(bitmap));
	FreeImage_Unload(bitmap);
}

/**
* Texture destructor frees unused resources
*/
Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

/**
* Render for textures
* @param renderMatrix texture render matrix (not used by this method)
*/
void Texture::render(glm::mat4 rendermatrix)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnable(GL_TEXTURE_2D);
}
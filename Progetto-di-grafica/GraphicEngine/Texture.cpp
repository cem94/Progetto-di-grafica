#include "Engine.h"
// FreeGLUT:
#include <GL/freeglut.h>

//// FreeImage:
#include <FreeImage.h>

Texture::Texture()
{
}
//TODO remove when project ends///////////////////////////////////////////
bool fileExist(const std::string& name) {
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

Texture::Texture(std::string textureName){
//TODO aggiungere texture valide e rimuovere questo//////////////////////////////////////////////////
	if (textureName.size() == 0 || textureName.compare("[none]")==0||textureName.size()==11) {
		std::cout << "Texture name not valid" << std::endl;
	}/////////////////////////////////////////////////////////////////
	else {
		std::cout << "Texture name size" << textureName.size() <<std::endl;
		std::cout << "Texture name " << textureName.c_str() <<std::endl;
		this->setName(textureName);
		glGenTextures(1, &textureId);
		std::string texturePath = "../resources/";
		const char* fileName = texturePath.append(textureName).c_str();

		//check fileName
		if (!fileExist(fileName)) {
			std::cout << "File " << textureName.c_str() << " not found. Current working directory: " << workingdir().c_str() << std::endl;
			exit(-1);
		}
		//create bitmap containing our texture
		FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(fileName, 0), fileName);
		//formati in/out
		int format = GL_RGB;
		GLenum extFormat = GL_BGR_EXT;
		//se l'immagine è a 32 bit usa RGBA -> TODO convertirle in 32
		if (FreeImage_GetBPP(bitmap) == 32)
		{
			format = GL_RGBA;
			extFormat = GL_BGRA_EXT;
		}
		// Update texture content:
		glBindTexture(GL_TEXTURE_2D, textureId);
		//TODO rimuovere è solo per testare ( genera le texture automaticamente -> non devo definire vertici texture)
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		////////////////////////////////////////////////////
		// Set circular coordinates:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//TODO aggiungere asintropia
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		// Set min/mag filters migliorano la texture rimuovendo errori
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//TODO controllare se OpenGL > 3.0 altrimenti mimapping non funziona
		// Using mipmapping 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//crea le mipmap
		gluBuild2DMipmaps(GL_TEXTURE_2D, format, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), extFormat, GL_UNSIGNED_BYTE, (void *)FreeImage_GetBits(bitmap));
		// Free resources: TODO usare metodi di Engine
		FreeImage_Unload(bitmap);
	}
}

//libera risorse
Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}
//renderizza la texture TODO capire perché renderMatrix non utilizzata
void Texture::render(glm::mat4 rendermatrix)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnable(GL_TEXTURE_2D);
}

Object::Type Texture::getType() const
{
	return TEXTURE;
}
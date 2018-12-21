/*
*The engine class is the main component of the API. It�s a single class (either static or singleton) responsible for initializing the OpenGL  context and main modules.
*
*/
#pragma once
#define GLM_FORCE_RADIANS
#ifdef _WINDOWS
#ifdef GAUNTLET_EXPORTS
#define LIB_API __declspec(dllexport)//windows necessita di questa macro per esportare la libreria come dll
#else
#define LIB_API __declspec(dllimport)
#endif
#else//linux
#define LIB_API
#endif

//C/C++
#include <iostream>
#include <vector>

//GLM
#define GLM_FORCE_CTOR_INIT               // Force constructors to initialize to identity from v0.9.9
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// CLASSES 
#include "Object.h"
#include "Node.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "List.h"

class LIB_API Engine
{
public:

	void  init(int argc, char *argv[]);

	void loadMatrix(glm::mat4 matrix);

	void startLoop();

	void clearColor(float r, float g, float b);

	void loadFile();

	void redisplay();

	void reshape(void(*reshapeCallback)(int, int));

	void display(void(*displayCallback)());

	void timer(void callback(int));

	void keyboard(void(*keyboardCallBack)(unsigned char, int, int));

	void specialKeyboard(void(*specialFunc)(int, int, int));

	void setViewport(int x, int y, int width, int height);

	void clearBuffers();

	void swapBuffers();

	void enableLighting(bool value);

	void renderText();

	void displayScene();

	void setProjectionMatrix(glm::mat4 projection, int type);

	void enableZbuffer();

	Camera* addCamera(std::string name, glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	//solo per debug -> rimuovere
	void rotate();
	void switchWireframe();
	void setRandomColors();
	void switchLights();
	
};

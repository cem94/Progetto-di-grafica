/*
 *The engine class is the main component of the API. Itís a single class (either
 *static or singleton) responsible for initializing the OpenGL  context and main
 *modules.
 */

#pragma once
#define GLM_FORCE_RADIANS
#ifdef _WINDOWS
#ifdef GAUNTLET_EXPORTS
// Windows necessita di questa macro per esportare la libreria come dll
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
// linux
#else
#define LIB_API
#endif

// C/C++
#include <limits.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// GLM
#define GLM_FORCE_CTOR_INIT  // Force constructors to initialize to identity
// (from v0.9.9)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/packing.hpp>
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
#include "OvoReader.h"

// Cambiata in singleton come scritto nelle slides
class LIB_API Engine
{
public:
    static Engine& getInstance();
    void init(int argc, char* argv[]);
    void loadMatrix(glm::mat4 matrix);
    void startLoop();
    void clearColor(float r, float g, float b);
    void mouseWheel(void (*mouseWheelFunc)(int, int, int, int));
    void mousePressed(int button, int state, int x, int y);
    void mousePressed(void (*mouseFunc)(int, int, int, int));
    int getWindowSizeX();
    int getWindowSizeY();
    void mouseMoved(void (*mouseFunc)(int, int));
    void redisplay();
    void reshape(void (*reshapeCallback)(int, int));
    void display(void (*displayCallback)());
    void timer(void callback(int));
    void keyboard(void (*keyboardCallBack)(unsigned char, int, int));
    void keyboardUp(void (*keyboardUpCallBack)(unsigned char, int, int));
    void specialKeyboard(void (*specialFunc)(int, int, int));
    void setViewport(int x, int y, int width, int height);
    void clearBuffers();
    void swapBuffers();
    void enableLight(Node* root, std::string lightName);
    void enableLighting(bool value);
    void renderText();
    void setProjectionMatrix(glm::mat4 projection);
    void enableZbuffer();
    void loadIdentity();
    void freeImageInitialize();
    void freeImageDeInitialize();
    Node* getScene(const char* name);
    void setCameraToPalm(Node* root);
    void addCamera(std::string name, bool movable, glm::vec3 eye,
                   glm::vec3 center, glm::vec3 up);
    bool isMovableCamera();
    void moveCameraRight(float direction);
    void moveCameraUp(float direction);
    void moveCameraForward(float direction);
    void rotateCameraRight(float angle);
    void rotateCameraUp(float angle);
    void switchLights();
    Node* getNodeByName(Node* root, std::string name);
    void changeCamera(Node* root);
    void createLists(Node* element);
    void renderList();
    void incrementFrames();
    void rotateModel(Node* root, float angle);
    void closeThumb(Node* root, float angle);
    void autoRotateModel(Node* root, float angle);
    void closeFinger(Node* root, int finger, float angle);
    void closeHand(Node* root, float angle);
    void free();
   // void transparentPreRender(Material* material, glm::mat4 renderMatrix);
    void sortTrasparentMeshesList(std::vector<Node*> transparentMeshes);
    void setAlphaToMaterial(Node* root, float alpha, std::string nodeName);
    void setLists(Node* root);
	Camera * getCurrentCamera();
	std::vector<List*> static getLists();
private:
    // Singleton
    Engine() {};                       // Private so that it can  not be called
    ~Engine();                         // private destructor
    Engine(Engine const&) {};          // copy constructor is private
    Engine& operator=(Engine const&);  // assignment operator is private
    static Engine* instance;
	static std::vector<List*> lists;
};

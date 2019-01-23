/**
 * The engine class is the main component of the API. It is a single class (singleton) responsible
 * for initializing the OpenGL  context and main modules.
 */

#pragma once
#define GLM_FORCE_RADIANS
#ifdef _WINDOWS
#ifdef GAUNTLET_EXPORTS
// Windows needs this macro for exporting the library as dll
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
// linux
#else
#define LIB_API
#endif
//So it doesn't give us deprecation warnings for fopen etc
#define _CRT_SECURE_NO_WARNINGS

// C/C++
#include <limits.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>

// GLM
// Force constructors to initialize to identity
#define GLM_FORCE_CTOR_INIT
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

class LIB_API Engine
{
public:
    static Engine& getInstance();
    void init();
    void loadMatrix(glm::mat4 matrix);
    void startLoop();
    void clearColor(float r, float g, float b);
    void mouseWheel(void(*mouseWheelFunc)(int, int, int, int));
    int getWindowWidth();
    int getWindowHeight();
    void mouseMoved(void(*mouseFunc)(int, int));
    void redisplay();
    void reshape(void(*reshapeCallback)(int, int));
    void display(void(*displayCallback)());
    void timer(void callback(int));
    void keyboard(void(*keyboardCallBack)(unsigned char, int, int));
    void keyboardUp(void(*keyboardUpCallBack)(unsigned char, int, int));
    void specialKeyboard(void(*specialFunc)(int, int, int));
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
    void addCamera(std::string name, bool movable, glm::vec3 eye,
                   glm::vec3 center, glm::vec3 up);
    void moveCamera(glm::mat4 move);
    void rotateCamera(glm::mat4 rotate);
    void switchLights();
    void moveLightForward(float direction);
    void moveLightRight(float direction);
    void moveLightUp(float direction);
    Node* getNodeByName(Node* root, std::string name);
    void changeCamera(Node* root);
    void incrementFrames();
    void rotateModel(Node* root, float angle);
    void closeThumb(Node* root);
    void openThumb(Node *root);
    void autoRotateModel(Node* root, float angle);
    void closeFinger(Node* root, int f);
    void openFinger(Node* root, int f);
    void closeHand(Node* root);
    void openHand(Node * root);
    void free();
    void setAlphaToMaterial(Node* root, float alpha, std::string nodeName);
    void createRenderList(Node* root);
    Camera * getCurrentCamera();
    glm::mat4 getCurrentCameraMatrix();
    bool isMovableCamera();
    void render();
private:
    Engine() {};
    ~Engine() {};
    Engine(Engine const&) {};
    Engine& operator=(Engine const&);
    static Engine* instance;
};
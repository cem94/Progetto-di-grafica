#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeGLUT:
#include <GL/freeglut.h>
class Engine
{
public:

    void initEngine(int width, int height);

    void renderMain(int argc, char *argv[]);

    void loadMatrix(glm::mat4 matrix);

    void startLoop();

    void clear();

    void clearColor(float r, float g, float b);

    void beginLines();

    void beginTriangles();

    void beginTriangleStrip();

    void end3D();

    void swapBuffer();

    void loadFile();

    void redisplay();
};

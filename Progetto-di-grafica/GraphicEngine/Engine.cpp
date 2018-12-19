#include "Engine.h"
#include <GL/freeglut.h>

void LIB_API Engine::initEngine(int width, int height)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
}

void LIB_API Engine::renderMain(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}
void LIB_API Engine::startLoop(){
    glutMainLoop();
}
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
    glLoadMatrixf(glm::value_ptr(matrix));
}

void LIB_API Engine::clear()
{
    glClearColor(1.0f, 1.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::clearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::beginLines()
{
    glBegin(GL_LINES);
}

void LIB_API Engine::beginTriangles()
{
    glBegin(GL_TRIANGLES);
}

void LIB_API Engine::beginTriangleStrip()
{
    glBegin(GL_TRIANGLE_STRIP);
}

void LIB_API Engine::end3D()
{
    glEnd();
}

void LIB_API Engine::swapBuffer()
{
    glutSwapBuffers();
}

void LIB_API Engine::loadFile()
{
    //TODO
}

void LIB_API Engine::redisplay()
{
    glutPostRedisplay();
}

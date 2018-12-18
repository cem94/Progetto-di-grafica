#include "Engine.h"

void Engine::initEngine(int width, int height)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
}

void Engine::renderMain(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}
void Engine::startLoop(){
    glutMainLoop();
}
void Engine::loadMatrix(glm::mat4 matrix)
{
    glLoadMatrixf(glm::value_ptr(matrix));
}

void Engine::clear()
{
    glClearColor(1.0f, 1.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::clearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::beginLines()
{
    glBegin(GL_LINES);
}

void Engine::beginTriangles()
{
    glBegin(GL_TRIANGLES);
}

void Engine::beginTriangleStrip()
{
    glBegin(GL_TRIANGLE_STRIP);
}

void Engine::end3D()
{
    glEnd();
}

void Engine::swapBuffer()
{
    glutSwapBuffers();
}

void Engine::loadFile()
{
    //TODO
}

void Engine::redisplay()
{
    glutPostRedisplay();
}

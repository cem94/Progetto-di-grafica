#include "Engine.h"
#include <GL/freeglut.h>
#include <iostream>
/////////////
// GLOBALS //
////////////
int windowId;
void LIB_API Engine::init(int argc, char *argv[])
{
	std::cout << "The engine starts" << std::endl;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	windowId = glutCreateWindow("Engine");
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
    glutPostWindowRedisplay(windowId);
}

void LIB_API Engine::reshape(void(*reshapeCallback)(int, int))
{
	glutReshapeFunc(reshapeCallback);
}

void LIB_API Engine::display(void(*displayCallback)())
{
	glutDisplayFunc(displayCallback);
}

void LIB_API Engine::timer(void callback(int))
{
	//TODO
	//glutTimerFunc(1000, callback, 0);
}

void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
}

void LIB_API Engine::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void Engine::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::swapBuffers()
{
	glutSwapBuffers();
}

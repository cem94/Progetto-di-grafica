#include "Engine.h"

void initEngine(int width, int height)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
}

void renderMain(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}
void startLoop(){
    glutMainLoop();
}
void loadMatrixGL(glm::mat4 matrix)
{
    glLoadMatrixf(glm::value_ptr(matrix));
}

void clear()
{
    glClearColor(1.0f, 1.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void clearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void beginLines()
{
    glBegin(GL_LINES);
}

void beginTriangles()
{
    glBegin(GL_TRIANGLES);
}

void beginTriangleStrip()
{
    glBegin(GL_TRIANGLE_STRIP);
}

void end3D()
{
    glEnd();
}

void swapBuffer()
{
    glutSwapBuffers();
}

void loadFile()
{
    //TODO
}

void redisplay()
{
    glutPostRedisplay();
}

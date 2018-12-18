// GLM:
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeGLUT:
#include <GL/gl.h>
#include <GL/freeglut.h>

void initEngine(int width, int height) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
}

void renderMain(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//TODO: set alla Callback
//	glutDisplayFunc(displayCallback);
//	glutReshapeFunc(reshapeCallback);
//	glutSpecialFunc(specialCallback);
//	glutKeyboardFunc(specialCallback);
//	glutMouseFunc(mouseCallback);
//	glutMotionFunc(dragCallback);

	glutMainLoop();
}

void loadMatrixGL(glm::mat4 matrix) {
	glLoadMatrixf(glm::value_ptr(matrix));
}

void clearGL() {
	glClearColor(1.0f, 1.0f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void clearGL(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void beginLinesGL() {
	glBegin(GL_LINES);
}

void beginTrianglesGL() {
	glBegin(GL_TRIANGLES);
}

void beginTriangleStripGL() {
	glBegin(GL_TRIANGLE_STRIP);
}

void end3DGL() {
	glEnd();
}

void swapBufferGL() {
	glutSwapBuffers();
}

void loadFileGL() {
	//TODO
}

void redisplayGL() {
	glutPostRedisplay();
}

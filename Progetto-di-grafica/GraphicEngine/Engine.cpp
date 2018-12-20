#include "Engine.h"

//FreeGlut//
#include <GL/freeglut.h>

/////////////
// GLOBALS //
////////////

int windowId;
float fps = 0.f;
int frames = 0;
//Camera TODO settarla
Camera *currentCamera = nullptr;
std::vector<Camera*> cameras;

void LIB_API Engine::init(int argc, char *argv[])
{
	std::cout << "The engine starts" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//setto opzioni finestra
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//creo finestra
	windowId = glutCreateWindow("Engine");
}

void LIB_API Engine::startLoop() {
	glutMainLoop();
}
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

void LIB_API Engine::clear()
{
	clearColor(0.f, 1.f, 0.f);
}

void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	clearBuffers();
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
	frames++;
	glutDisplayFunc(displayCallback);
}

void LIB_API Engine::timer(void callback(int))
{
	//calcolo fps
	fps = frames / 1.0f;
	frames = 0;
	glutTimerFunc(1000, callback, 0);
	std::cout << fps << std::endl;
}

void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
	redisplay();
}

void Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
	redisplay();
}

void LIB_API Engine::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void LIB_API Engine::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::swapBuffers()
{
	glutSwapBuffers();
}
void LIB_API Engine::displayCube(float edge)
{
	float size = edge / 2.0f;
	// Back:
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(-size, size, -size);
	glEnd();

	// Front:
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glEnd();

	// Left:
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glEnd();

	// Right:
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glEnd();

	// Bottom:
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(size, -size, size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glEnd();

	// Top:
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, -size);
	glVertex3f(-size, size, -size);
	glEnd();
	//redisplay();
}
//setta la matrice di proiezione per la camera
void LIB_API Engine::setProjectionMatrix(glm::mat4 projection, int type)
{
	currentCamera->setProjectionMatrix(projection);
	//TODO magari spostare in metodo loadIdentity
	if (type == 1)
	{
		loadMatrix(glm::mat4(1.f));
	}
}
void LIB_API Engine::enableZbuffer()
{
	glEnable(GL_DEPTH_TEST);
}
//abilita/disabilita l'illuminazione(per renderizzare in 2D (testo etc)
void LIB_API Engine::enableLighting(bool value)
{
	if (value) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}
}
//scrive info su schermo (FPS etc)
void LIB_API Engine::renderText()
{
	//TODO scrivere i comandi del guanto / opzioni / fps
	char text[64];
	strcpy_s(text, "Some text");
	//colore testo
	glColor3f(1.0f, 1.0f, 1.0f);
	//x,y del testo 
	glRasterPos2f(10.0f, 20.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	strcpy_s(text, "Some text2");//cambiato da strcpy il compilatore dice che è più sicuro strcpy_s
	glRasterPos2f(10.0f, 40.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	strcpy_s(text, "Some text3");
	glRasterPos2f(10.0f, 60.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
}
//aggiunge una camera alla scena TODO far si che si possa cambiare camera
Camera LIB_API *Engine::addCamera(std::string name, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera *camera = new Camera();
	camera->setName(name);
	camera->setMatrix(glm::lookAt(eye, center, up));
	//aggiunge la camera all'elenco
	cameras.push_back(camera);
	//e la setta come camera corrente
	currentCamera = camera;
	return currentCamera;
}

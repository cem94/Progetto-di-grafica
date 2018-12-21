#include "Engine.h"

//FreeGlut//
#include <GL/freeglut.h>

/////////////
// GLOBALS //
////////////

int windowId;
float fps = 0.f;
int frames = 0;
float angleY = 0.0f;
float angleX = 0.0f;
bool lighting = false;
//Cameras
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
	//cos� posso controllare quando chiuderla p.e premendo un bottone
	/*while (condition) {
		glutMainLoopEvent();
	}*/
	glutMainLoop();
}
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void LIB_API Engine::loadFile()
{
	//TODO
}

void LIB_API Engine::redisplay()
{
	glutPostWindowRedisplay(windowId);
	frames++;
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
	//calcolo fps
	fps = frames / 1.0f;
	frames = 0;
	glutTimerFunc(1000, callback, 0);
	std::cout << fps << std::endl;
}

void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
	//glutPostRedisplay();
	//redisplay();
}

void Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
//	redisplay();
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
void LIB_API Engine::displayScene()
{
	
	glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -45.0f));
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 f = translation * rotation;

	// Set model matrix as current OpenGL matrix:
	glLoadMatrixf(glm::value_ptr(f));
	// Red color used to draw.
	glColor3f(0.8, 0.2, 0.1);
	glutSolidTeacup(10); 
	glColor3f(0.8, 1.0, 0.1);
	glTranslated(30, 0, -30);
	glutSolidTeapot(10);
	//glutSwapBuffers();
}

//setta
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
		lighting = true;
		glEnable(GL_LIGHTING);
	}
	else {
		lighting = false;
		glDisable(GL_LIGHTING);
	}
}
//scrive info su schermo (FPS etc)
void LIB_API Engine::renderText()
{
	//TODO scrivere i comandi del guanto / opzioni / fps
	char text[64];
	//cambiato da strcpy il compilatore dice che � pi� sicuro strcpy_s
	strcpy_s(text, "Some text");
	//colore testo
	glColor3f(0.0f, 1.0f, 1.0f);
	//x,y del testo 
	glRasterPos2f(10.0f, 20.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	if (lighting) {
		strcpy_s(text, "Lighting on");
	}
	else {
		strcpy_s(text, "Lighting off");
	}
	
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

void Engine::rotate()
{
	angleX++;
	angleY++;	
}

#include "Engine.h"
// GLOBALS //
Engine* engine = new Engine();
//matrici di proiezione
glm::mat4 perspective;
glm::mat4 ortho;


void displayCallback() {
	//clear dei bit COLOR/DEPTH
	engine->clearColor(1,0,0);
	engine->clearBuffers();
	//setto la matrice di proiezione prospettica per il rendering 3d
	engine->setProjectionMatrix(perspective, 0);

	//3d rendering
	//TODO capire perché non funziona
	engine->displayCube(20);
	//2D rendering
	/////////////////////////////////////////////////////////////
	//setto la matrice di proiezione ortogonale il rendering 2d
	engine->setProjectionMatrix(ortho, 1);
	engine->enableLighting(false);
	//stampo informazioni
	engine->renderText();
	engine->enableLighting(true);
	/////////////////////////////////////////////////////////////
	//swappa il buffer mostrando ciò che è stato renderizzato
	//engine->incrementFrames();
	engine->swapBuffers();
	engine->redisplay();
}

void reshapeCallback(int width, int height) {
	std::cout << "reshape func invoked" << std::endl;
	engine->setViewport(0, 0, width, height);
	//perspective:(fieldOfView,aspectRatio,nearPlane, farPlane)
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 150.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}
void keyboardCallback(unsigned char key, int mouseX, int mouseY) {
	switch (key)
	{
	case 'w':
		engine->clearColor(1, 0, 0);//non funziona perché?
		std::cout << "w pressed" << std::endl;
		break;
	case 's':
		break;
	case 'a':
		break;
	case 'd':
		break;

	}
	engine->redisplay();
}
void specialCallback(int key, int x, int y) {
	switch (key) {
	//TODO
}
	engine->redisplay();
}
void timerCallback(int value) {
	//si può fare?
	engine->timer(timerCallback);
}
int main(int argc, char * argv[])
{
	std::cout << "Client application starts" << std::endl;
	engine->init(argc, argv);
	//setta callback
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	engine->timer(timerCallback);

	//abilita z buffer / depth test
	engine->enableZbuffer();
	engine->clearColor(0.0f, 0.0f, 1.0f);

	//dove si trova la camera
	glm::vec3 eye = glm::vec3(0.f, 100.f, -100.f);
	//verso dove guarda 
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	//dove è il sopra
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//aggiunge la prima camera
	engine->addCamera("1", eye, center, up);
	//main loop
	engine->startLoop();
	std::cout << "Application terminated" << std::endl;
}

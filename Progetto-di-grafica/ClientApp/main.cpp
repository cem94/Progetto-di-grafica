#include "Engine.h"
// GLOBALS //
Engine* engine = new Engine();
//matrici di proiezione
glm::mat4 perspective;
;
glm::mat4 ortho;


void displayCallback() {
	//engine->setViewport(0, 0, 1920, 1080);
	engine->clearBuffers();
	//setto la matrice di proiezione prospettica per il rendering 3d
	engine->setProjectionMatrix(perspective, 0);
	//3d rendering//
	//TODO capire perché non funziona
	engine->displayScene();


	//2D rendering//
	//setto la matrice di proiezione ortogonale il rendering 2d
	engine->setProjectionMatrix(ortho, 1);
	engine->enableLighting(false);
	//stampo informazioni
	engine->renderText();
	engine->enableLighting(true);
	//swappa il buffer mostrando ciò che è stato renderizzato
	//engine->incrementFrames();
	engine->swapBuffers();
	engine->redisplay();
}

void reshapeCallback(int width, int height) {
	std::cout << "reshape func invoked" << std::endl;
	engine->setViewport(0, 0, width, height);
	//perspective:(fieldOfView,aspectRatio,nearPlane, farPlane)
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}
void keyboardCallback(unsigned char key, int mouseX, int mouseY) {
	switch (key)
	{
	case 'w':
		
		break;
	case 's':
		break;
	case 'a':
		engine->clearColor(0, 0, 1);
		break;
	case 'd':
		engine->rotate();
		break;

	}

//	engine->redisplay();
}
void specialCallback(int key, int x, int y) {
	switch (key) {
	default:
		break;
		//Ideally, only GLM should be used client-side.
	//TODO If needed, replicate the (few) required definitions in your engine’s include files(e.g., the definition of special keys provided by FreeGlut).
}
	//engine->redisplay();
}
void timerCallback(int value) {
	//si può fare?
	engine->timer(timerCallback);
}
int main(int argc, char * argv[])
{
	std::cout << "Client application starts" << std::endl;
	engine->init(argc, argv);
	//set callback
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	engine->specialKeyboard(specialCallback);
	engine->timer(timerCallback);
	// Global OpenGL settings:
	//setta il colore con cui verra dipinto lo sfondo -> per colorare lo sfondo uso clearBuffers
	engine->clearColor(1.0f,0.0f,0.0f);
	//abilita z buffer
	//engine->enableZbuffer();
	//abilita illuminazione
	//engine->enableLighting(true);
	// CAMERA //
	//dove si trova la camera
	glm::vec3 eye = glm::vec3(0.f, 0.f, -45.f);
	//verso dove guarda 
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	//dove è il sopra
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//aggiunge la prima camera	TODO potrei creare le camere già qui e passargli l'oggetto
	engine->addCamera("1", eye, center, up);
	//main loop
	engine->startLoop();
	std::cout << "Application terminated" << std::endl;

}

#include <iostream>
#include "Engine.h"
#include "main.h"
// GLOBALS //
Engine* engine = new Engine();
//matrix
glm::mat4 perspective;
glm::mat4 ortho;

void displayCallback() {
	//sfondo
	engine->clearColor(0.f, 1.f, 1.f);
	//clear dei bit COLOR/DEPTH
	engine->clearBuffers();
	//TODO render scene
	//swappa il buffer mostrando ciò che è stato renderizzato
	engine->swapBuffers();
	engine->redisplay();
}

void reshapeCallback(int width, int height) {
	engine->setViewport(0, 0, width, height);
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}
void keyboardCallback(unsigned char key, int mouseX, int mouseY){
	std::cout << "key pressed" << std::endl;
	switch (key)
	{
	case 'w':
		break;
	case 's':
		break;
	case 'a':
		break;
	case 'd':
		break;
	}
}

void timerCallback(int value) {
	//si può fare?
	engine->timer(timerCallback);
}
int main(int argc, char * argv[])
{
    std::cout << "Client application starts"<<std::endl;
	engine->init(argc, argv);
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	engine->timer(timerCallback);
	//TODO
	//engine->enableZBuffer();
	engine->startLoop();
    std::cout << "Application terminated"<<std::endl;
}

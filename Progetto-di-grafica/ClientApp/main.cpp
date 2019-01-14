#include "Engine.h"
// GLOBALS //
Engine* engine = new Engine();
//matrici di proiezione
glm::mat4 perspective;
glm::mat4 ortho;
Node *root = NULL;
//Ideally, only GLM should be used client-side.
//TODO If needed, replicate the (few) required definitions in your engine’s include files(e.g., the definition of special keys provided by FreeGlut).
#define GLUT_KEY_LEFT 0x0064
#define GLUT_KEY_UP 0x0065
#define GLUT_KEY_RIGHT 0x0066
#define GLUT_KEY_DOWN 0x0069


void displayCallback() {
	//clear dei bit DEPTH etc
	engine->clearBuffers();

	//TODO setto la camera sull'oggetto principale
	engine->setCameraToNode(root, "1", "palmo");

	//setto la matrice di proiezione prospettica per il rendering 3d
	engine->setProjectionMatrix(perspective);
	//we pass the scene graph
	engine->pass(root, glm::mat4(1.0f));
	//3d rendering//
	//renderizza la lista ottenuta dal file OVO
	engine->renderList();
	/* TODO far muovere il guanto in automatico o qualcosa così
	->trasformazioni etc
	if (moving)
	{
			speed = speed + 0.1;
	}
	else
	{
			speed = speed - 0.1;
	}
	engine->moveGauntlet(root, speed);
	*/

	//2D rendering//
	//setto la matrice di proiezione ortogonale il rendering 2d
	engine->setProjectionMatrix(ortho);
	//necessario (la matrice è ortogonale)
	engine->loadIdentity();
	engine->renderText();
	//TODO testare e vedere se serve
	engine->incrementFrames();
	//swappa il buffer mostrando ciò che è stato renderizzato
	engine->swapBuffers();
	engine->redisplay();
}

void reshapeCallback(int width, int height) {
	engine->setViewport(0, 0, width, height);
	//perspective:							(fieldOfView,		aspectRatio,			 nearPlane, farPlane)
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 4000.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}

void keyboardCallback(unsigned char key, int mouseX, int mouseY) {
	switch (key)
	{
		//Così dovrebbe essere comoda da usare//
		//pollice
	case ' ':
		//engine->closeFinger();
		break;
		//indice
	case 'd':
		//engine->closeFinger();
		break;
		//medio
	case 'w':
		//engine->closeFinger();
		break;
		//anulare
	case 'a':
		//engine->closeFinger();
		break;
		//mignolo
			//16 =  shift
	case 16:
		//engine->closeFinger();
		break;
	case 'l':
		//abilita/disabilita luci 
		engine->switchLights();
		break;

		//muovi mano
	case 'm':
		//engine->moveHand();
		break;
		//cambia camera corrente
	case 'c':
		engine->changeCamera();
		//set nome camera corrente
		break;
	case 'p':
		break;
	}
	//necessario?
		engine->redisplay();

}

void specialCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	default:
		break;

	}
	//necessario?
	engine->redisplay();
}

void timerCallback(int value) {
	//si può fare?
	engine->timer(timerCallback);
}

//zoom in / out
void mouseWheel(int wheel, int direction, int x, int y)
{
	wheel = 0;
	if (direction == -1)
	{
		glm::vec3 traslation(0.0, 0.0, -10);
		engine->moveCamera(traslation);
	}
	else if (direction == +1)
	{
		glm::vec3 traslation(0.0, 0.0, 10);
		engine->moveCamera(traslation);
	}
}
//callback per pressione mouse
void mousePressed(int button, int state, int x, int y)
{
	engine->mousePressed(button, state, x, y);
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
	engine->mouseWheel(mouseWheel);
	engine->mousePressed(mousePressed);

	engine->timer(timerCallback);
	//forse si possono spostare in init
	engine->enableZbuffer();
	engine->freeImageInitialize();

	//setta il colore con cui verra dipinto lo sfondo -> per colorare lo sfondo uso clearBuffers
	engine->clearColor(0.2f, 0.3f, 0.0f);

	//dove si trova la camera
	glm::vec3 eye = glm::vec3(200.f, 500.f, 1200.f);
	//verso dove guarda 
	glm::vec3 center = glm::vec3(200.0f, 0.0f, 0.0f);
	//dove è il sopra
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	engine->addCamera("1", eye, center, up);
	engine->addCamera("2", eye, center, up);

	const char* fileName = "../ovo_files/gauntlet.ovo";
	root = engine->getRoot(fileName);
	std::cout << "Ovo file readed " << std::endl;
	engine->startLoop();
	//forse si può spostare in engine->free o qualcosa così
	engine->freeImageDeInitialize();
	std::cout << "Application terminated" << std::endl;
}

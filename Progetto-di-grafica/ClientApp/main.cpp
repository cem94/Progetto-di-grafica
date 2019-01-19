#include "Engine.h"
#define GLUT_KEY_LEFT 0x0064
#define GLUT_KEY_UP 0x0065
#define GLUT_KEY_RIGHT 0x0066
#define GLUT_KEY_DOWN 0x0067
#define BUTTON_UP 0
#define BUTTON_DOWN 1

// GLOBALS //
Engine* engine = &Engine::getInstance();
// matrici di proiezione
glm::mat4 perspective;
glm::mat4 ortho;
Node* scene = NULL;
bool rotating = false;
int sizeX = 0;
int sizeY = 0;
float angleX = 0.0f;
//button state machine
bool keyState[255];

/**
 * Display callback
 */
void displayCallback()
{
	// clear dei bit DEPTH etc
	engine->clearBuffers();
	// setto la matrice di proiezione prospettica per il rendering 3d
	engine->setProjectionMatrix(perspective);
	// 3d rendering//
	engine->renderList();
	if (rotating)
		engine->autoRotateModel(scene, -1.0f);
	// 2D rendering//
	engine->setProjectionMatrix(ortho);
	engine->loadIdentity();
	engine->enableLighting(false);
	engine->renderText();
	engine->enableLighting(true);
	engine->incrementFrames();
	engine->swapBuffers();
	engine->redisplay();
}
/**
 * Reshape callback
 * @param width screen width
 * @param height screen height
 */
void reshapeCallback(int width, int height)
{
	engine->setViewport(0, 0, width, height);
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 4000.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
	engine->updateSize();
}
/**
 * Keyboard callback
 * @param  key the button that was pressed
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
	//pressed
	keyState[key] = true;
	switch (key)
	{
	case '1':
		engine->enableLight(scene, "fix_light");
		break;
	case '2':
		engine->enableLight(scene, "Omni1");
		break;
	case '3':
		engine->enableLight(scene, "Omni2");
		break;
	case '4':
		engine->enableLight(scene, "Omni3");
		break;
	case 'r':
		engine->rotateModel(scene, 1);
		break;
	case 'R':
		rotating = !rotating;
		break;
	case 'c':
		//TODO:: vedere di farlo meglio!
		engine->changeCamera(scene);
		break;
	case 'h':
		if (keyState[(unsigned char)'h'] == true)
		{
			engine->closeHand(scene, 5.f);
		}
		break;
	case ' ':
		if (keyState[(unsigned char)' '] == true) {
			engine->closeThumb(scene, 5.f);
		}
		break;
	case 'f':
		if (keyState[(unsigned char)'f'] == true) {
			engine->closeFinger(scene, 1, 5.f);
		}
		break;
	case 'e':
		if (keyState[(unsigned char)'e'] == true) {
			engine->closeFinger(scene, 2, 5.f);
		}
		break;

	case 'w':
		if (keyState[(unsigned char)'w'] == true) {
			engine->closeFinger(scene, 3, 5.f);
		}
		break;
	case 'a':
		if (keyState[(unsigned char)'a'] == true) {
			engine->closeFinger(scene, 4, 5.f);
		}
		break;
	}
	engine->redisplay();
}

/**
 * Keyboard up callback
 * @param  key the button that was released
 * @param x x coordinate
 * @param x y coordinate
 */
void keyboardUpCallback(unsigned char key, int x, int y)
{
	//not pressed
	keyState[key] = false;
	switch (key) {
	case 'h':
		if (keyState[(unsigned char)'h'] == false) {
			engine->closeHand(scene, -1.f);
		}
		break;
	case ' ':
		if (keyState[(unsigned char)' '] == false) {
			engine->closeThumb(scene, -1.f);
		}
		break;
	case 'f':
		if (keyState[(unsigned char)'f'] == false) {
			engine->closeFinger(scene, 1, -1.f);
		}
		break;
	case 'e':
		if (keyState[(unsigned char)'e'] == false) {
			engine->closeFinger(scene, 2, -1.f);
		}
		break;
	case 'w':
		if (keyState[(unsigned char)'w'] == false) {
			engine->closeFinger(scene, 3, -1.f);
		}
		break;
	case 'a':
		if (keyState[(unsigned char)'a'] == false) {
			engine->closeFinger(scene, 4, -1.f);

		}
		break;
	}
}

/**
 * Special callback
 * @param  key an integer representing a special key
 * @param x x coordinate
 * @param y y coordinate
 */
void specialCallback(int key, int x, int y)
{
	//muovi luce
	if (!engine->isMovableCamera())
		return;
	switch (key) {
	case GLUT_KEY_DOWN:
		engine->moveCameraZ(-1.0f);
		break;
	case GLUT_KEY_LEFT:
		engine->moveCameraX(1.0f);
		break;
	case GLUT_KEY_RIGHT:
		engine->moveCameraX(-1.0f);
		break;
	case GLUT_KEY_UP:
		engine->moveCameraZ(1.0f);
		break;
	default:
		break;
	}
	engine->redisplay();
}
/**
 * Timer callback
 * @param  value
 */
void timerCallback(int value)
{
	engine->timer(timerCallback);
}

/**
 * Mouse wheel callback that implement a zoom function
 * @param wheel the value of the mouse wheel
 * @param direction the direction in which the wheel is scrolled
 * @param x x coordinate
 * @param y y coordinate
 */
void mouseWheel(int wheel, int direction, int x, int y)
{
	wheel = 0;
	if (!engine->isMovableCamera())
		return;
	if (direction == -1)
		engine->moveCamera(-10); //engine->moveCamera(glm::vec3(0,-1,0));
	else if (direction == +1)
		engine->moveCameraY(10);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void mouseMoved(int x, int y) {
  // UP
  if (x > sizeX * 0.25 && x < sizeX * 0.75 && y < sizeY * 0.25) {
    std::cout << "UP" << std::endl;
	// DOWN
  } else if (x > sizeX * 0.25 && x < sizeX * 0.75 && y > sizeY * 0.75) {
    std::cout << "DOWN" << std::endl;
    // LEFT
  } else if (y > sizeY * 0.25 && y < sizeY * 0.75 && x < sizeX * 0.25) {
    std::cout << "left" << std::endl;
    // RIGHT
  } else if (y > sizeY * 0.25 && y < sizeY * 0.75 && y > sizeX * 0.75) {
    std::cout << "Right" << std::endl;
  }
}

/**
 * Mouse pressed callback
 * @param  button mouse button that was pressed
 * @param state the state of the button
 * @param x x coordinate
 * @param y y coordinate
 */
void mousePressed(int button, int state, int x, int y)
{
	engine->mousePressed(button, state, x, y);
}

/**
 * Callback setter
 */
void setCallBacks()
{
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	//necessario
	engine->keyboardUp(keyboardUpCallback);
	engine->specialKeyboard(specialCallback);
	engine->mouseWheel(mouseWheel);
    engine->mouseMoved(mouseMoved);
	//eliminare se non lo usiamo
	engine->mousePressed(mousePressed);
	engine->timer(timerCallback);
}
/**
 * Camera setter
 */
void setCameras() {
	// dove si trova la camera
	glm::vec3 eye = glm::vec3(0.f, 50.f, 400.f);
	// verso dove guarda
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	// dove è il sopra
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	engine->addCamera("3", false, eye, center, up);
	eye = glm::vec3(-400.f, 400.f, 400.f);
	engine->addCamera("2", false, eye, center, up);
	//si direbbe che renderizza prima l'ultima che gli passi quindi questa è la camera 1
  //lascialo così se no non vedo la scena
	eye = glm::vec3(0, 50, 400.f);
    center = glm::vec3(0.0f, 0.0f, 0.0f);
	engine->addCamera("1", true, eye, center, up);
}

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
	std::cout << "Client application starts" << std::endl;
	// init engine settings
	engine->init(argc, argv);
	
	sizeY = engine->getWindowSizeY();
    sizeX = engine->getWindowSizeX();

	// init call back functions
	setCallBacks();
	// set background color
	engine->clearColor(1.f, 1.f, 1.f);
	// set cameras
	setCameras();
	// read ovo file, load scene and start main loop
	const char* fileName = "../ovo_files/full_scene.ovo";
	scene = engine->getScene(fileName);
	engine->setLists(scene);
	//TRASPARENZE per ora non funzionano -> da completare
	engine->setAlphaToMaterial(scene, 0.9f, "plane");
	//TODO:  così è come ha fatto Gatto io non so come usare quella matrice. Se sai come farlo fallo tu pf
	glm::mat4 reflection = glm::scale(glm::mat4(), glm::vec3(1.0f, -1.0f, 1.0));
	engine->setLists(scene,reflection);	

	engine->updateSize();
    sizeX = engine->getWindowSizeX();
	sizeY = engine->getWindowSizeY();

	engine->startLoop();
	engine->freeImageDeInitialize();
	std::cout << "Application terminated" << std::endl;
}
#include "Engine.h"
#define GLUT_KEY_LEFT 0x0064
#define GLUT_KEY_UP 0x0065
#define GLUT_KEY_RIGHT 0x0066
#define GLUT_KEY_DOWN 0x0067
// GLOBALS //
Engine* engine = &Engine::getInstance();
// matrici di proiezione
glm::mat4 perspective;
glm::mat4 ortho;
Node* scene = NULL;
bool rotating = false;
float angle = 0.0f;
#define BUTTON_UP   0
#define BUTTON_DOWN 1

unsigned char keyState[255];
unsigned char mouseState[3];

// Cameras
/*Camera* currentCamera = nullptr;
std::vector<Camera*> cameras;
int activeCamera = 1;
*/
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void displayCallback()
{
	// clear dei bit DEPTH etc
	engine->clearBuffers();
	// setto la matrice di proiezione prospettica per il rendering 3d
	engine->setProjectionMatrix(perspective);
	// 3d rendering//
	// renderizza la lista ottenuta dal file OVO
	engine->renderList();
	if (rotating)
		engine->rotateModel(scene, -3);
	// 2D rendering//
	// setto la matrice di proiezione ortogonale il rendering 2d
	engine->setProjectionMatrix(ortho);
	// necessario (la matrice Ë ortogonale)
	engine->loadIdentity();
	engine->enableLighting(false);
	engine->renderText();
	engine->enableLighting(true);
	// TODO testare e vedere se serve
	engine->incrementFrames();
	// swappa il buffer mostrando cio che e stato renderizzato
	engine->swapBuffers();
	engine->redisplay();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void reshapeCallback(int width, int height)
{
	engine->setViewport(0, 0, width, height);
	perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 4000.0f);
	ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
	keyState[key] = BUTTON_DOWN;
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
		//indice
	case 'r':
		engine->rotateModel(scene, 1);
		break;
		//rotazione automatica
	case 'R':
		rotating = !rotating;
		break;
		//cambia camera corrente
	case 'c':
		engine->changeCamera();
		break;
	}
	//Controlli mano

	if (keyState[(unsigned char)'h'] == BUTTON_DOWN) 
	{
			engine->closeHand(scene, 5.f);	
	}
	else if (keyState[(unsigned char)' '] == BUTTON_DOWN) {
		engine->closeFinger(scene, 0, 5.f);
	}
	else if (keyState[(unsigned char)'f'] == BUTTON_DOWN)
	{
		engine->closeFinger(scene, 1,5.f);
	}
	else if (keyState[(unsigned char)'e'] == BUTTON_DOWN)
	{
		engine->closeFinger(scene, 2, 5.f);
	}
	else if (keyState[(unsigned char)'w'] == BUTTON_DOWN)
	{
		engine->closeFinger(scene, 3, 5.f);
	}
	else if (keyState[(unsigned char)'a'] == BUTTON_DOWN)
	{
		engine->closeFinger(scene, 4, 5.f);
	}
	engine->redisplay();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */

void keyboardUpCallback(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_UP;
	if (keyState[(unsigned char)'h'] == BUTTON_UP) {
		printf("Up\n");
		engine->closeHand(scene, -1.f);
		}
	else if (keyState[(unsigned char)' '] == BUTTON_UP) {
		engine->closeFinger(scene,0, -1.f);
	}
	else if (keyState[(unsigned char)'f'] == BUTTON_UP) {
		engine->closeFinger(scene,1, -1.f);
	}
	else if (keyState[(unsigned char)'e'] == BUTTON_UP) {
		engine->closeFinger(scene, 2, -1.f);
	}
	else if (keyState[(unsigned char)'w'] == BUTTON_UP) {
		engine->closeFinger(scene, 3, -1.f);
	}
	else if (keyState[(unsigned char)'a'] == BUTTON_UP) {
		engine->closeFinger(scene, 4, -1.f);
	}
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
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
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void timerCallback(int value)
{
	engine->timer(timerCallback);
}

//zoom in / out
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void mouseWheel(int wheel, int direction, int x, int y)
{
	wheel = 0;
    if (!engine->isMovableCamera())
		return;
	if (direction == -1 )
		engine->moveCamera(-10); //engine->moveCamera(glm::vec3(0,-1,0));
	else if (direction == +1)
		engine->moveCamera(10);
}

//callback per pressione mouse
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void mousePressed(int button, int state, int x, int y)
{
	engine->mousePressed(button, state, x, y);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void setCallBacks()
{
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	//engine->keyboardUp(keyboardUpCallback);
	engine->specialKeyboard(specialCallback);
	engine->mouseWheel(mouseWheel);
	//eliminare se non lo usiamo
	engine->mousePressed(mousePressed);
	engine->timer(timerCallback);
}

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
    eye = glm::vec3(200, 200, 0.f);
	engine->addCamera("1", true, eye, center, up);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int main(int argc, char* argv[])
{
	std::cout << "Client application starts" << std::endl;
	// init engine settings
	engine->init(argc, argv);
	// init call back functions
	setCallBacks();
	// set background color
	engine->clearColor(0.2f, 0.3f, 0.7f);
	// set cameras
	setCameras();
	// read ovo file, load scene and start main loop
	const char* fileName = "../ovo_files/full_scene.ovo";
	scene = engine->getScene(fileName);
	engine->setLists(scene);
	//TRASPARENZE per ora non funzionano -> da completare
	engine->setAlphaToMaterial(scene, 0.9f, "plane");
	//TODO:: GREG GUARDA SULLE SLIDE C'È SCRITTO COME FARE -> (1.0f, 0.0f, 1.0f) ->  così è come ha fatto Gatto io non so come usare quella matrice. Se sai come farlo fallo tu pf
	
	glm::mat4 reflection = glm::scale(glm::mat4(), glm::vec3(1.0f, -1.0f, 1.0));
	engine->setLists(scene,reflection);	
	
	engine->startLoop();

	//TODO:: FreeImage_DeInitialise
	std::cout << "Application terminated" << std::endl;
}
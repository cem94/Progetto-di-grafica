#include "Engine.h"
// GLOBALS //
Engine* engine = new Engine();
// matrici di proiezione
glm::mat4 perspective;
glm::mat4 ortho;
Node* scene = NULL;
bool autoRotate = false;
// Ideally, only GLM should be used client-side.
// TODO If needed, replicate the (few) required definitions in your engineís
// include files(e.g., the definition of special keys provided by FreeGlut).
#define GLUT_KEY_LEFT 0x0064
#define GLUT_KEY_UP 0x0065
#define GLUT_KEY_RIGHT 0x0066
#define GLUT_KEY_DOWN 0x0069

void displayCallback() {
  // clear dei bit DEPTH etc
  engine->clearBuffers();

  // setto la matrice di proiezione prospettica per il rendering 3d
  engine->setProjectionMatrix(perspective);

  // we pass the scene graph
  // engine->pass(scene, glm::mat4(1.0f));

  // 3d rendering//
  // renderizza la lista ottenuta dal file OVO
  engine->renderList();
  /* TODO far muovere il guanto in automatico o qualcosa cosÏ
   */
  // engine->rotate(scene, angle);
  // TODO:: deve essere modulo 360

  if (autoRotate) 
	  engine->rotateModel(scene, -3);
  // 2D rendering//
  // setto la matrice di proiezione ortogonale il rendering 2d
  engine->setProjectionMatrix(ortho);
  // necessario (la matrice Ë ortogonale)
  engine->loadIdentity();
  engine->renderText();
  // TODO testare e vedere se serve
  engine->incrementFrames();
  // swappa il buffer mostrando ciÚ che Ë stato renderizzato
  engine->swapBuffers();
  engine->redisplay();
}

void reshapeCallback(int width, int height) {
  engine->setViewport(0, 0, width, height);
  // perspective:							(fieldOfView,		aspectRatio,
  // nearPlane, farPlane)
  perspective = glm::perspective(glm::radians(45.0f),
                                 (float)width / (float)height, 1.0f, 700.0f);
  ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}

void keyboardCallback(unsigned char key, int mouseX, int mouseY) 
{
	switch (key)
	{
		//Così dovrebbe essere comoda da usare//
	case '1':
		//TODO accendere /spegnere luce1,2 ,3 etc

		//pollice
	case ' ':
		engine->closeThumb(scene);
		break;
		//indice
	case 'd':
		engine->closeFinger(scene,"indice");
		break;
		//medio
	case 'w':
		engine->closeFinger(scene,"medio");
		break;
		//anulare
	case 'a':
		engine->closeFinger(scene,"anulare");
		break;
		//mignolo
	//TODO capire qual'è lo shift e cambiare
	case 'e':
		engine->closeFinger(scene,"mignolo");
		break;
	case 'l':
		//abilita/disabilita illuminazione 
		engine->switchLights();
		break;
		//muovi mano
	case 'r':
		engine->rotateModel(scene,1);
		break;
    case 'R':
        autoRotate = !autoRotate;
        break;
        //cambia camera corrente
	case 'c':
		engine->changeCamera();
		//set nome camera corrente
		break;
	case 'p':
	engine->enableLight(scene, "fix_light");
		break;

	}
	engine->redisplay();
}

void specialCallback(int key, int x, int y) 
{
	//muovi luce
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
	engine->redisplay();
}

void timerCallback(int value) { engine->timer(timerCallback); }

//zoom in / out
void mouseWheel(int wheel, int direction, int x, int y)
{
	// TODO:: come possiamo usarlo?
	wheel = 0;
	if (direction == -1) {
		engine->moveCamera(-1.0f);
	} else if (direction == +1) {
		engine->moveCamera(1.0f);
	}
}

//callback per pressione mouse
void mousePressed(int button, int state, int x, int y)
{
	engine->mousePressed(button, state, x, y);
}

void initCamera()
{
	// dove si trova la camera
	glm::vec3 eye = glm::vec3(420.f, 400.f, 400.f);
	// verso dove guarda
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	// dove è il sopra
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	engine->addCamera("1", eye, center, up);
	engine->addCamera("2", eye, center, up);
}

// TODO:: vedere quali ci servono e quali no. 
void initCallBackFunction()
{
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	engine->specialKeyboard(specialCallback);
	engine->mouseWheel(mouseWheel);
	engine->mousePressed(mousePressed);
	engine->timer(timerCallback);
}

int main(int argc, char* argv[]) {
  std::cout << "Client application starts" << std::endl;

  // init engine settings
  engine->init(argc, argv);

	// init call back functions
	initCallBackFunction();
	// set background color
	engine->clearColor(0.2f, 0.3f, 0.7f);
	
	// init camera
	initCamera();

	// read ovo file, load scene and start main loop
	const char* fileName = "../ovo_files/gauntlet.ovo";
	scene = engine->getScene(fileName);
	//L'ho spostato qua sembra funzionare
	engine->pass(scene);
	
	// setto la camera sull'oggetto principale
    engine->setCameraToNode(scene, "2", "guardia");

	//engine->changeCamera();

	engine->startLoop();
	// free memory
	delete (engine);
	
	std::cout << "Application terminated" << std::endl;
}
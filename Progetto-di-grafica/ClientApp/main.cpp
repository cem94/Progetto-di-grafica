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
int sizeX = 0;
int sizeY = 0;
float angleX = 0.0f;
// button state machine
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

	engine->render();
	/*std::vector<List*> lists = Engine::getLists();
	for (int i = 0; i < lists.size(); i++) {
		lists.at(i)->render(glm::mat4(1.0f));
		//printf("Rendering %d\n",i);
	}*/

	// printf("Rendering %d\n",i);
    if (rotating)
        engine->autoRotateModel(scene, -1.0f);
    // 2D rendering//
    engine->setProjectionMatrix(ortho);
    engine->loadIdentity();
    engine->renderText();
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
    sizeX = width;
    sizeY = height;
    perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 4000.0f);
    ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 1.f);
}
/**
 * Keyboard callback
 * @param  key the button that was pressed
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
    // pressed
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
	case '5':
		engine->enableLight(scene, "moving_light");
		engine->enableLight(scene, "specular_light");
		break;
	case 'r':
		engine->rotateModel(scene, 1);
		break;
	case 'R':
		rotating = !rotating;
		break;
	case 'c':
		engine->changeCamera(scene);
		break;
	case 'h':
		if (keyState[(unsigned char)'h'] == true)
		{
			engine->closeHand(scene);
		}
		break;
	case ' ':
		if (keyState[(unsigned char)' '] == true)
		{
			engine->closeThumb(scene);
		}
		break;
	case 'f':
		if (keyState[(unsigned char)'f'] == true)
		{
			engine->closeFinger(scene, 1);
		}
		break;
	case 'e':
		if (keyState[(unsigned char)'e'] == true)
		{
			engine->closeFinger(scene, 2);
		}
		break;

	case 'w':
		if (keyState[(unsigned char)'w'] == true)
		{
			engine->closeFinger(scene, 3);
		}
		break;
	case 'a':
		if (keyState[(unsigned char)'a'] == true)
		{
			engine->closeFinger(scene, 4);
		}
		break;
	case 'i':
		engine->moveLightForward(3.0f);
		break;
	case 'j':
		engine->moveLightRight(-3.0f);
		break;
	case 'k':
		engine->moveLightForward(-3.0f);
		break;
	case 'l':
		engine->moveLightRight(3.0f);
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
    // not pressed
    keyState[key] = false;
    switch (key)
    {
    case 'h':
        if (keyState[(unsigned char)'h'] == false)
        {
            engine->openHand(scene);
        }
        break;
    case ' ':
        if (keyState[(unsigned char)' '] == false)
        {
			//NON FUNZIONA IL POLLICE SI DEFORMA
           // engine->openThumb(scene);
        }
        break;
    case 'f':
        if (keyState[(unsigned char)'f'] == false)
        {
            engine->openFinger(scene, 1);
        }
        break;
    case 'e':
        if (keyState[(unsigned char)'e'] == false)
        {
            engine->openFinger(scene, 2);
        }
        break;
    case 'w':
        if (keyState[(unsigned char)'w'] == false)
        {
            engine->openFinger(scene, 3);
        }
        break;
    case 'a':
        if (keyState[(unsigned char)'a'] == false)
        {
            engine->openFinger(scene, 4);
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
    // muove camere
    switch (key)
    {
    case GLUT_KEY_DOWN:
        engine->moveCameraForward(-3.0f);
        break;
    case GLUT_KEY_UP:
        engine->moveCameraForward(3.0f);
        break;
    case GLUT_KEY_LEFT:
        engine->moveCameraRight(3.0f);
        break;
    case GLUT_KEY_RIGHT:
        engine->moveCameraRight(-3.0f);
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
    else if (direction == -1)
        engine->moveCameraUp(1.0f);
    else if (direction == +1)
        engine->moveCameraUp(-1.0f);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void mouseMoved(int x, int y)
{
    //TODO:: chiedere a Marco
    // UP
    const float sizeYMin = sizeY * 0.20;
    const float sizeXMin = sizeX * 0.20;
    const float sizeYMax = sizeY * 0.80;
    const float sizeXMax = sizeX * 0.80;

    if (x > sizeXMin && x < sizeXMax && y < sizeYMin)
    {
       // std::cout << "UP" << std::endl;
        const float angle = (10.0f / sizeYMin) * (sizeYMin - y);
        engine->rotateCameraUp(-angle);
        // DOWN
    }
    else if (x > sizeXMin && x < sizeXMax && y > sizeYMax)
    {
      //  std::cout << "DOWN" << std::endl;
        const float angle = (10.0f / (sizeY - sizeYMax)) * (y - sizeYMax);
        engine->rotateCameraUp(angle);
        // LEFT
    }
    else if (y > sizeYMin && y < sizeYMax && x < sizeXMin)
    {
      //  std::cout << "LEFT" << std::endl;
        const float angle = (10.0f / sizeXMin) * (sizeXMin - x);
        engine->rotateCameraRight(-angle);
        // RIGHT
    }
    else if (y > sizeYMin && y < sizeYMax && x > sizeXMax)
    {
     //   std::cout << "RIGHT" << std::endl;
        const float angle = (10.0f / (sizeX - sizeXMax)) * (x - sizeXMax);
        engine->rotateCameraRight(angle);
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
    // necessario
    engine->keyboardUp(keyboardUpCallback);
    engine->specialKeyboard(specialCallback);
    engine->mouseWheel(mouseWheel);
    engine->mouseMoved(mouseMoved);
    // eliminare se non lo usiamo
    engine->mousePressed(mousePressed);
    engine->timer(timerCallback);
}
/**
 * Camera setter
 */
void setCameras()
{
    // dove si trova la camera
    glm::vec3 eye = glm::vec3(0.f, 150.f, 400.f);
    // verso dove guarda
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    // dove è il sopra
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    engine->addCamera("Camera3", false, eye, center, up);
    eye = glm::vec3(400.f, 400.f, 400.f);
    engine->addCamera("Camera2", false, eye, center, up);
    // si direbbe che renderizza prima l'ultima che gli passi quindi questa è la
    // camera 1
    // lascialo così se no non vedo la scena
    eye = glm::vec3(0.0f, 50.0f, 400.f);
    center = glm::vec3(0.0f, 50.0f, 200.0f);
    engine->addCamera("Camera1", true, eye, center, up);
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
    // init call back functions
    setCallBacks();
    // set background color
    engine->clearColor(1.f, 1.f, 1.f);
    // set cameras
    setCameras();
    // read ovo file, load scene and start main loop
    const char* fileName = "../ovo_files/full_scene.ovo";
    scene = engine->getScene(fileName);

	// engine->setAlphaToMaterial(scene, 0.9f, "plane");
	engine->setLists(scene);
   
	//TODO Cem basta farlo in reshape callback lo chiama una volta anche all'inizio
    sizeX = engine->getWindowSizeX();
    sizeY = engine->getWindowSizeY();
	//start main loop
    engine->startLoop();
    //free resources
	engine->free();
    std::cout << "Application terminated" << std::endl;
}

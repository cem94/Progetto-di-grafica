#include "Engine.h"
//Defines for Freeglut keys
#define GLUT_KEY_LEFT 0x0064
#define GLUT_KEY_UP 0x0065
#define GLUT_KEY_RIGHT 0x0066
#define GLUT_KEY_DOWN 0x0067

/////////////
// GLOBALS //
////////////

Engine* engine = &Engine::getInstance();
// projection matrix
glm::mat4 perspective;
glm::mat4 ortho;
//scene graph
Node* scene = nullptr;
bool rotating = false;
int sizeX = 0;
int sizeY = 0;

/**
 * Display callback  this is the main rendering routine
 */
void displayCallback()
{
	// clear of buffer and depth bits
	engine->clearBuffers();
	//set perspective matrix for 3d rendering
	engine->setProjectionMatrix(perspective);
	// 3d rendering//
	engine->render();
	if (rotating)
		engine->autoRotateModel(scene, -1.0f);
	// 2D rendering//
	engine->setProjectionMatrix(ortho);
	engine->loadIdentity();
	//render some text
	engine->renderText();
	engine->incrementFrames();
	engine->swapBuffers();
	engine->redisplay();
}

/**
 * Reshape callback this callback is invoked each time the window gets resized (and once also when created).
 * @param width window width
 * @param height window height
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
 * Keyboard callback  this callback is invoked each time a standard keyboard key is pressed.
 * @param  key the button that was pressed
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
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
		engine->enableLight(scene, "moving_light");
		engine->enableLight(scene, "specular_light");
		break;
	case 'r':
		if (!rotating)
			engine->rotateModel(scene, 8);
		break;
	case 'R':
		rotating = !rotating;
		break;
	case 'c':
		engine->changeCamera(scene);
		break;
	case 'k':
		engine->moveLightForward(10.0f);
		break;
	case 'l':
		engine->moveLightRight(-10.0f);
		break;
	case 'i':
		engine->moveLightForward(-10.0f);
		break;
	case 'j':
		engine->moveLightRight(10.0f);
		break;
	case 'u':
		engine->moveLightUp(-10.0f);
		break;
	case 'o':
		engine->moveLightUp(10.0f);
		break;
	case 'H':
		engine->moveHand(scene, true);
		break;
	case 'h':
		engine->moveHand(scene, false);
		break;
	case 'A':
		engine->moveFinger(scene, 4, true);
		break;
	case 'a':
		engine->moveFinger(scene, 4, false);
		break;
	case 'S':
		engine->moveFinger(scene, 3, true);
		break;
	case 's':
		engine->moveFinger(scene, 3, false);
		break;
	case 'D':
		engine->moveFinger(scene, 2, true);
		break;
	case 'd':
		engine->moveFinger(scene, 2, false);
		break;
	case 'F':
		engine->moveFinger(scene, 1, true);
		break;
	case 'f':
		engine->moveFinger(scene, 1, false);
		break;
	case 'G':
		engine->moveFinger(scene, 0, true);
		break;
	case 'g':
		engine->moveFinger(scene, 0, false);
		break;
	default:
		break;
	}
	engine->redisplay();
}


/**
 * Special callback is invoked each time a special keyboard key is pressed. This callback is used to move 
 * the camera (if movable). FreeGlut special key redefinition is necessary (e.g #define GLUT_KEY_LEFT 0x0064)
 * @param  key an integer representing a special key
 * @param x x coordinate
 * @param y y coordinate
 */
void specialCallback(int key, int mouseX, int mouseY)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
	{
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
        glm::vec3 mov = -15.0f * matrix[2];
		engine->moveCamera(matrix * glm::translate(glm::mat4(1.0f), mov));
        break;
	}
    case GLUT_KEY_UP:
	{
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
		glm::vec3 mov = 15.0f * matrix[2];
		engine->moveCamera(matrix * glm::translate(glm::mat4(1.0f), mov));
		break;
	}
    case GLUT_KEY_LEFT: 
	{
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
		glm::vec3 mov = 15.0f * matrix[0];
		engine->moveCamera(matrix * glm::translate(glm::mat4(1.0f), mov));
		break;
	}
    case GLUT_KEY_RIGHT: 
	{
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
		glm::vec3 mov = -15.0f * matrix[0];
		engine->moveCamera(matrix * glm::translate(glm::mat4(1.0f), mov));
		break;
	}
    default:
        break;
    }
    engine->redisplay();
}

/**
 * Timer callback is used to register fps updates
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
	if (direction == -1)
	{
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
        glm::vec3 mov = 15.0f * matrix[1];
        engine->moveCamera(glm::translate(matrix *glm::mat4(1.0f), mov));
	} else if (direction == +1) {
		glm::mat4 matrix = engine->getCurrentCameraMatrix();
		glm::vec3 mov = -15.0f * matrix[1];
		engine->moveCamera(glm::translate(matrix * glm::mat4(1.0f), mov));
	}
}

/**
 * Mouse motion callback
 * @param  x
 * @param y
 */
void mouseMoved(int x, int y)
{
	const float sizeYMin = sizeY * 0.20;
    const float sizeXMin = sizeX * 0.20;
    const float sizeYMax = sizeY * 0.80;
    const float sizeXMax = sizeX * 0.80;
    const bool movable = engine->isMovableCamera();
    // UP
    if (x > sizeXMin && x < sizeXMax && y < sizeYMin && movable)
    {
		const float angle = (2.0f / sizeYMin) * (sizeYMin - y);
		glm::mat4 mat = engine->getCurrentCameraMatrix();
		glm::vec3 vec = mat[0];
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), vec);
		engine->rotateCamera(rotation * mat);
    }
    // DOWN
    else if (x > sizeXMin && x < sizeXMax && y > sizeYMax && movable)
    {
		const float angle = (2.0f / (sizeY - sizeYMax)) * (y - sizeYMax);
		glm::mat4 mat = engine->getCurrentCameraMatrix();
		glm::vec3 vec = mat[0];
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec);
		engine->rotateCamera(rotation * mat);
    }
    // LEFT
    else if (y > sizeYMin && y < sizeYMax && x < sizeXMin && !movable)
    {
        const float angle = (5.0f / sizeXMin) * (sizeXMin - x);
		glm::mat4 mat = engine->getCurrentCameraMatrix();
		glm::vec3 vec = mat[1];
		glm::mat4 rotation =glm::rotate(glm::mat4(1.0f), glm::radians(-angle), vec);
        engine->rotateCamera(rotation * mat);
    }
    // RIGHT
    else if (y > sizeYMin && y < sizeYMax && x > sizeXMax && !movable)
    {
        const float angle = (5.0f / (sizeX - sizeXMax)) * (x - sizeXMax);
		glm::mat4 mat = engine->getCurrentCameraMatrix();
		glm::vec3 vec = mat[1];
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec);
		engine->rotateCamera(rotation * mat);
    }
}

/**
 * Callback setter
 */
void setCallBacks()
{
	engine->display(displayCallback);
	engine->reshape(reshapeCallback);
	engine->keyboard(keyboardCallback);
	engine->specialKeyboard(specialCallback);
	engine->mouseWheel(mouseWheel);
	engine->mouseMoved(mouseMoved);
	engine->timer(timerCallback);
}

/**
 * Camera setter
 */
void setCameras()
{
	glm::vec3 eye = glm::vec3(400.f, 150.f, 300.f);
	glm::vec3 center = glm::vec3(0.f, 50.f, -50.f);
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	engine->addCamera("Camera3", false, eye, center, up);
	eye = glm::vec3(-450.f, 330.f, 350.f);
	engine->addCamera("Camera2", false, eye, center, up);
	eye = glm::vec3(0.0f, 50.0f, 220.f);
	center = glm::vec3(0.0f, 50.0f, -150.0f);
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
	engine->init();
	// init call back functions
	setCallBacks();
	// set background color
	engine->clearColor(0.529f, 0.808f, 0.922f);
	// set cameras
	setCameras();
	// load ovo file
	const char* fileName = "../ovo_files/complete_scene.ovo";
	// read ovo file, load scene and start main loop
	scene = engine->getScene(fileName);
	engine->createRenderList(scene);
	//start main loop
	engine->startLoop();
	//free resources
	engine->free();
	std::cout << "Application terminated" << std::endl;
}
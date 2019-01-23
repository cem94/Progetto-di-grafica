#include "Engine.h"

//Glew//
#include <GL/glew.h>

// FreeGlut//
#include <GL/freeglut.h>

// FreeImage
#include <FreeImage.h>

/////////////
// GLOBALS //
////////////

int windowId;
// performance options
float fps = 0.f;
int frames = 0;

//Light options
bool lighting = true;

//Cameras
Camera* currentCamera = nullptr;
std::vector<Camera*> cameras;
int activeCamera = 0;

//Light
Light* movableLight = nullptr;
Light* specularLight = nullptr;
Mesh* globeLight = nullptr;

//Fingers options
const float sensitivity = 5.f;
float fingerAngles[5];
std::string fingerNames[5] = { "pollice", "indice", "medio", "anulare", "mignolo" };

//Gauntlet rotation options
bool translateUp = false;
int translateCounter;

//list of istances to render
List* toRender = new List();
Engine* Engine::instance = nullptr;

/**
 * Getter for engine instance
 * @return a instance of engine. A new instance is created if engine is still nullptr
 */
Engine LIB_API & Engine::getInstance()
{
	if (instance == nullptr)
		instance = new Engine{};
	return *instance;
}

/**
 * Init function
 */
void LIB_API Engine::init()
{
	freeImageInitialize();
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	int argc = 1;
	glutInit(&argc, nullptr);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	windowId = glutCreateWindow("Engine");
	glewExperimental = GL_TRUE;  // Optional, but recommended
	glEnable(GL_NORMALIZE);
	// Init glew
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Error loading GLEW
		printf("Error loading GLEW\n");
	}
	else if (!glewIsSupported("GL_VERSION_2_1"))
	{
		// Required OpenGL version not supported
		printf("Required OpenGL version not supported\n");
	}
	enableLighting(true);
	glEnable(GL_LIGHT0);
	enableZbuffer();
}

/**
 * Start the main loop
 */
void LIB_API Engine::startLoop()
{
	glutMainLoop();
}

/**
 * Wrapper function that loads matrix as the current Opengl matrix
 * @param matrix the matrix to set
 */
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

/**
 * Setter for clear color
 * @param r red component of the color
 * @param g green component of the color
 * @param b blue component of the color
 */
void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

/**
 * Setter for mouse wheel callback
 * @param mouseWheelFunc the mouse callback to set
 */
void LIB_API Engine::mouseWheel(void(*mouseWheelFunc)(int, int, int, int))
{
	glutMouseWheelFunc(mouseWheelFunc);
}

/**
 * Get windows width
 * @return current window width
 */
int LIB_API Engine::getWindowWidth()
{
	return glutGet(GLUT_WINDOW_WIDTH);
}

/**
 * Get windows height
 * @return current widows height
 */
int LIB_API Engine::getWindowHeight()
{
	return glutGet(GLUT_WINDOW_HEIGHT);
}

/**
 * Callback for mouse passive motion function
 * @param mouveMoved passive motion function callback
 */
void LIB_API Engine::mouseMoved(void(*mouseMoved)(int, int))
{
	glutPassiveMotionFunc(mouseMoved);
}

/**
 * Wrapper function for glutPostWindowRedisplay
 */
void LIB_API Engine::redisplay()
{
	glutPostWindowRedisplay(windowId);
}

/**
 * Setter for reshape callback
 * @param reshapeCallback reshape callback to set
 */
void LIB_API Engine::reshape(void(*reshapeCallback)(int, int))
{
	glutReshapeFunc(reshapeCallback);
}

/**
 * Setter for display callback
 * @param displayCallback display callback to set
 */
void LIB_API Engine::display(void(*displayCallback)())
{
	glutDisplayFunc(displayCallback);
}

/**
 * Setter for timer callback here we calculate fps
 * @param timerCallback
 */
void LIB_API Engine::timer(void timerCallback(int))
{
	fps = frames / 1.0f;
	frames = 0;
	// Register the next update:
	glutTimerFunc(1000, timerCallback, 0);
}

/**
 * Setter for keyboard callback
 * @param keyboardCallBack keyboard callback to set
 */
void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
	glutPostWindowRedisplay(windowId);
}

/**
 * Setter for special keyboard callback
 * @param  specialFunc special keyboard callback to set
 */
void LIB_API Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
	glutPostWindowRedisplay(windowId);
}

/**
 * Setter for OpenGL viewport
 * @param x x coordinate
 * @param y y coordinate
 * @param width viewport width
 * @param height viewport height
 */
void LIB_API Engine::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

/**
 * Clear the color and depth buffer bit
 */
void LIB_API Engine::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Wrapper for glutSwapBuffers
 */
void LIB_API Engine::swapBuffers()
{
	glutSwapBuffers();
}

/**
 * Loads the identity matrix
 */
void LIB_API Engine::loadIdentity()
{
	loadMatrix(glm::mat4(1.0f));
}

/**
 * Initialize Free Image
 */
void Engine::freeImageInitialize()
{
	FreeImage_Initialise();
}

/**
* DeInitialize Free Image
*/
void Engine::freeImageDeInitialize()
{
	FreeImage_DeInitialise();
}

/**
 * Setter for current camera projection matrix
 * @param  projection camera projection matrix
 */
void LIB_API Engine::setProjectionMatrix(glm::mat4 projection)
{
	currentCamera->setProjectionMatrix(projection);
}

/**
 * Enable Z buffer
 */
void LIB_API Engine::enableZbuffer()
{
	glEnable(GL_DEPTH_TEST);
}

/**
 * Changes lighting state
 */
void LIB_API Engine::switchLights()
{
	lighting = !lighting;
	enableLighting(lighting);
}

/**
 * Move light forward or backwards according to the value of direction
 * direction direction of the light (positive forward negative backwards)
 */
void LIB_API Engine::moveLightForward(float direction)
{
	glm::mat4 matrix = movableLight->getMatrix();
	glm::vec3 mov = direction * 5.0f * matrix[0];
	glm::mat4 trans = glm::translate(matrix, mov);
	if (trans[3].x > 90.0f || trans[3].x < -89.0f)
		return;
	movableLight->setMatrix(trans);
	specularLight->setMatrix(trans);
	glm::mat4 matrixObj = globeLight->getMatrix();
	matrixObj[3] = (movableLight->getMatrix())[3];
	globeLight->setMatrix(matrixObj);
}

/**
 * Move light right or left according to the value of direction
 * direction direction of the light (positive right negative left)
 */
void LIB_API Engine::moveLightRight(float direction)
{
	glm::mat4 matrix = movableLight->getMatrix();
	glm::vec3 mov = direction * 5.0f * matrix[2];
	glm::mat4 trans = glm::translate(matrix, mov);
	if (trans[3].z > 94.0f || trans[3].z < -94.0f)
		return;
	movableLight->setMatrix(trans);
	specularLight->setMatrix(trans);
	glm::mat4 matrixObj = globeLight->getMatrix();
	matrixObj[3] = (movableLight->getMatrix())[3];
	globeLight->setMatrix(matrixObj);
}

/**
 * Move light up or down according to the value of direction
 * direction direction of the light (positive up negative down)
 */
void LIB_API Engine::moveLightUp(float direction)
{
	glm::mat4 matrix = movableLight->getMatrix();
	glm::vec3 mov = direction * 5.0f * matrix[1];
	glm::mat4 trans = glm::translate(matrix, mov);
	if (trans[3].y > 83.0f || trans[3].y < 3.0f)
		return;
	movableLight->setMatrix(trans);
	specularLight->setMatrix(trans);
	glm::mat4 matrixObj = globeLight->getMatrix();
	matrixObj[3] = (movableLight->getMatrix())[3];
	globeLight->setMatrix(matrixObj);
}

/**
 * Enable or disable illumination according to the boolean value passed as argument
 * @param  value true = enable lights false = disable lights
 */
void LIB_API Engine::enableLighting(bool value)
{
	if (value)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}

/**
 * Change light state given its name
 * @param  scene scene graph
 * @param lightName the name of the light to enable
 */
void LIB_API Engine::enableLight(Node *scene, std::string lightName)
{
	Light* light = static_cast<Light *>(getNodeByName(scene, lightName));
	if (light != nullptr)
		light->changeState();
}

/**
 * Starting from current node it recursively populate the scene graph according to its capacity
 * @param  currentNode the current node
 * @param nodes the list of remaining nodes to insert
 */
void LIB_API findChildren(Node* currentNode, std::vector<Node*>& nodes)
{
	const int capacity = currentNode->getCapacity();
	for (int i = 0; i < capacity; i++)
	{
		Node* next = nodes.at(0);
		nodes.erase(nodes.begin());
		currentNode->insert(next);
		findChildren(next, nodes);
	}
}

/**
* Returns the scene graph given its name
* @param  name OVO file name
* @return root node of the scene graph
*/
Node*  Engine::getScene(const char* name)
{
	std::vector<Node*> nodes = OvoReader::readOVOfile(name);
	Node* root = nodes.at(0);
	nodes.erase(nodes.begin());
	findChildren(root, nodes);
	movableLight = (Light*)getNodeByName(root, "moving_light");
	specularLight = (Light*)getNodeByName(root, "specular_light");
	globeLight = (Mesh*)getNodeByName(root, "sphere_light");
	printTree(root, "");
	return root;
}

/**
 * takes a node from scene graph searching it by his name
 * @param root node and node name
 */
Node*  Engine::getNodeByName(Node* root, std::string name)
{
	if (root->getName().compare(name) == 0)
		return root;
	else
	{
		for (Node* n : root->getChildren())
		{
			Node* founded = getNodeByName(n, name);
			if (founded != nullptr)
				return founded;
		}
		return nullptr;
	}
}

/**
  * Create render list and sort it
  * @param root scene graph
  */
void  LIB_API Engine::createRenderList(Node * root)
{
	setAlphaToMaterial(root, 0.5f, "plane");
	toRender = new List(root);
	toRender->sort();
}

/**
 * Get current camera
 * @return current camera
 */
Camera * Engine::getCurrentCamera()
{
	return currentCamera;
}

/**
 * Get current camera matrix
 * @return current camera matrix
 */
glm::mat4 Engine::getCurrentCameraMatrix()
{
	return currentCamera->getMatrix();
}

/**
 * Get current camera movable property
 * @return current camera movable value
 */
bool LIB_API Engine::isMovableCamera()
{
	return currentCamera->getMovable();
}

/**
 * Render scene
 */
void LIB_API Engine::render()
{
	glm::mat4 mat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f));
	toRender->isReflection(true);
	//clockwise
	glFrontFace(GL_CW);
	toRender->render(mat);
	//counter clockwise
	glFrontFace(GL_CCW);
	toRender->isReflection(false);
	toRender->render(mat);
}

/**
 * Render some 2D text with various information
 */
void LIB_API Engine::renderText()
{
	enableLighting(false);
	glDisable(GL_TEXTURE_2D);
	char text[64];
	strcpy(text, "[1] [2] [3] [4] turn on/off lights");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 40.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	/*-----------------------------------------------------------*/
	sprintf(text, "FPS: %.1f", fps);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 60.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	/*-----------------------------------------------------------*/
	strcpy(text, "[c] change camera");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 80.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	/*-----------------------------------------------------------*/
	sprintf(text, "[r] rotate model");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 100.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

	/*-----------------------------------------------------------*/
	sprintf(text, "[a] [s] [d] [f] [g] close fingers ");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 100.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

	/*-----------------------------------------------------------*/
	sprintf(text, "[h] close hand ");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 120.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	/*-----------------------------------------------------------*/
	sprintf(text, "[j][k][l][i] move light left forwards up or backwards");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 140.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	/*-----------------------------------------------------------*/
	sprintf(text, "[u][o] move light up and down");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(10.0f, 160.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	glEnable(GL_TEXTURE_2D);
	enableLighting(true);
}

/**
 * Increment frames
 */
void LIB_API Engine::incrementFrames()
{
	frames++;
}

/**
 * Add a camera to cameras list
 * @param name camera name
 * @param movable movable value
 * @param eye where the eye is
 * @param center center of the scene
 * @param up orientation vector
 */
void LIB_API Engine::addCamera(std::string name, bool movable, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera* camera = new Camera();
	camera->setName(name);
	camera->setMovable(movable);
	camera->setType(Object::Type::CAMERA);
	camera->setMatrix(glm::lookAt(eye, center, up));
	cameras.push_back(camera);
	currentCamera = camera;
	activeCamera = static_cast<int>(cameras.size() - 1);
}

/**
 * Limits for camera movement
 * @param move movement matrix
 */
void LIB_API Engine::moveCamera(glm::mat4 move)
{
	if (!currentCamera->getMovable())
		return;
	if (move[3][1] > 0.0f)
		return;
	if (move[3][2] > 400.0f || move[3][2] < -400.0f)
		return;
	if (move[3][0] > 630.0f || move[3][0] < -630.0f)
		return;
	currentCamera->setMatrix(move);
}

/**
 * Rotate the camera
 * @param rotate rotation to apply
 */
void Engine::rotateCamera(glm::mat4 rotate)
{
	  currentCamera->setMatrix(rotate);
}

/**
* Change the current camera
*/
void LIB_API Engine::changeCamera(Node * root)
{
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
}

/**
 * Rotate model
 * @param  root scene graph
 * @param angle rotational increment
 */
void LIB_API Engine::rotateModel(Node * root, float angle)
{
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		guardia->setMatrix(guardia->getMatrix()*rotation);
	}
}

/**
 * Automatic rotation of the model with some additional effects
 * @param  root scene graph
 * @param angle rotation angle
 */
void Engine::autoRotateModel(Node* root, float angle)
{
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translate;
		translateCounter++;
		if (translateUp)
			translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
		else
			translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

		guardia->setMatrix(guardia->getMatrix() * translate * rotation);

		if (translateCounter > 180)
		{
			translateCounter = 0;
			translateUp = !translateUp;
		}
	}
}

/**
 * Move the thumb
 * @param  root scene graph
 * @param open boolean value that determines the closure or opening of the thumb (true open false close)
 */
void LIB_API Engine::moveThumb(Node *root, bool open)
{
	glm::mat4 rotation;
	if (open)
	{
		if (fingerAngles[0] == 0.f)
		{
			return;
		}
		fingerAngles[0] -= sensitivity;
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(sensitivity), glm::vec3(-1.0f, 1.0f, 1.0f));

	}
	else
	{
		if (fingerAngles[0] > 65.f)
		{
			return;
		}
		fingerAngles[0] += sensitivity;
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(sensitivity), glm::vec3(1.0f, -1.0f, -1.0f));

	}
	std::string name = fingerNames[0];
	name.append("2");
	Node* phalanx2 = getNodeByName(root, name);
	Node* phalanx1 = phalanx2->getParent();
	phalanx1->setMatrix(phalanx1->getMatrix()*rotation);
	phalanx2->setMatrix(phalanx2->getMatrix()*rotation);
}

/**
 * Move a finger of the hand
 * @param  scene scene graph
 * @param f number of the finger to close (starting from 0)
 * @param open boolean value that determines the closure or opening of the finger (true open false close)
 */
void LIB_API Engine::moveFinger(Node * root, int f, bool open)
{
	if (f == 0)
	{
		moveThumb(root, open);
		return;
	}
	glm::mat4 rotation;
	if (open)
	{
		//limit reached
		if (fingerAngles[f] == 0)
		{

			return;
		}
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(sensitivity), glm::vec3(0.0f, 0.0f, 1.0f));
		fingerAngles[f] -= sensitivity;
	}
	else
	{
		//limit reached
		if (fingerAngles[f] > 75.f)
		{
			return;
		}
		fingerAngles[f] += sensitivity;
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(sensitivity), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	std::string name = fingerNames[f];
	name.append("3");
	Node* phalanx3 = getNodeByName(root, name);
	Node* phalanx2 = phalanx3->getParent();
	Node* phalanx1 = phalanx2->getParent();
	phalanx1->setMatrix(phalanx1->getMatrix()*rotation);
	phalanx2->setMatrix(phalanx2->getMatrix()*rotation);
	phalanx3->setMatrix(phalanx3->getMatrix()*rotation);
}

/**
 * Move hand
 * @param root scene graph
 * @param open boolean value that determines the closure or opening of the hand (true open false close)
 */
void LIB_API Engine::moveHand(Node * root, bool open)
{
	moveFinger(root, 0, open);
	moveFinger(root, 1, open);
	moveFinger(root, 2, open);
	moveFinger(root, 3, open);
	moveFinger(root, 4, open);
}

/**
 * Function that set alpha to a desired material
 * @param scene scene graph
 * @param alpha alpha value to set
 * @param materialName name of the material
 */
void LIB_API Engine::setAlphaToMaterial(Node * root, float alpha, std::string materialName)
{
	Node* node = getNodeByName(root, materialName);
	if (node != nullptr)
	{
		Mesh* mesh = (Mesh*)node;
		mesh->getMaterial()->setAlpha(alpha);
	}
}

/**
 * Function that prints the scene graph
 * @param  scene the scene graph to print
 * @param indentation text intentation
 */
void Engine::printTree(Node* scene, std::string indentation)
{
	std::cout << indentation.c_str() << scene->getName().c_str() << std::endl;
	for (int i = 0; i < scene->getChildrenSize(); i++)
		printTree(scene->getChildren().at(i), "\t - " + indentation);
}

/**
 * Function that frees unused resources
 */
void LIB_API Engine::free()
{
	freeImageDeInitialize();
}
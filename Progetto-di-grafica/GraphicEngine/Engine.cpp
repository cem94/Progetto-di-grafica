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
// performance properties
float fps = 0.f;
int frames = 0;
// options
bool lighting = true;
// Cameras
Camera* currentCamera = nullptr;
std::vector<Camera*> cameras;
int activeCamera = 0;

float fingerAngles[5];
//per il pollice
float angleX;
std::string fingerNames[5] = { "pollice", "indice","medio","anulare","mignolo" };
//TODO:: se riusciamo a fare un reserve
List* toRender = new List();
List *trasparentMeshes = new List();
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
 * @param  argc number of command-line arguments passed
 * @param argv  containing up to argc passed arguments
 */
void LIB_API Engine::init(int argc, char* argv[])
{
	freeImageInitialize();
	std::cout << "The engine starts" << std::endl;
	// setto opzioni finestra
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInit(&argc, argv);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// creo finestra
	windowId = glutCreateWindow("Engine");

	//COSA SONO QUESTE DUE COSE ?????
	glewExperimental = GL_TRUE;  // Optional, but recommended
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
	glEnable(GL_NORMALIZE);

	// Init di glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Error loading GLEW
		printf("Error loading GLEW\n");
	}
	else if (!glewIsSupported("GL_VERSION_2_1")) {
		// Required OpenGL version not supported
		printf("Required OpenGL version not supported\n");
	}

	//TODO:: GREG serie 7 riga 579, il sore fa:
	// glGenTextures(1, &texId);   
	// buildTexture(false);
	// a cosa server avere un id per le texture??

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
 * @param  matrix the matrix to set
 */
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

/**
 *Setter for clear color 
 * @param r r component of the color
 * @param g g component of the color
 * @param b b component of the color
 */
void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

/**
 * Setter for mouse wheel callback
 * @param  mouseWheelFunc the mouse callback to set
 */
void LIB_API Engine::mouseWheel(void(*mouseWheelFunc)(int, int, int, int))
{
	glutMouseWheelFunc(mouseWheelFunc);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::mousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_UP) {
		// isMousePressed = false;
	}
	if (state == GLUT_DOWN) {
		// isMousePressed = true;
		// mousePosition.x = x;
		// mousePosition.y = y;
	}
}

/**
 * Setter for mouse pressed callback
 * @param mouseFunc mouse pressed callback function to set
 */
void LIB_API Engine::mousePressed(void(*mouseFunc)(int, int, int, int))
{
	glutMouseFunc(mouseFunc);
}

/**
 * Wrapper for redisplay
 */
void LIB_API Engine::redisplay()
{
	glutPostWindowRedisplay(windowId);
}

/**
 * Setter for reshape callback
 * @param  reshapeCallback reshape callback to set
 */
void LIB_API Engine::reshape(void(*reshapeCallback)(int, int))
{
	glutReshapeFunc(reshapeCallback);
}

/**
 * Setter for display callback
 * @param  displayCallback display callback to set
 */
void LIB_API Engine::display(void(*displayCallback)())
{
	glutDisplayFunc(displayCallback);
}

/**
 * Setter for timer callback
 * @param  timerCallback
 * @param2 name2
 */
void LIB_API Engine::timer(void timerCallback(int))
{
	// calcolo fps -> da completare
	fps = frames / 1.0f;
	frames = 0;
	// Register the next update:
	glutTimerFunc(1000, timerCallback, 0);
}
/**
 * Setter for keyboard callback
 * @param  keyboardCallBack keyboard callback to set
 */
void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
}
/**
 * Setter for keyboard up callback
 * @param  keyboardUpCallBack keyboard up callback to set
 */
void LIB_API Engine::keyboardUp(void(*keyboardUpCallBack)(unsigned char, int, int))
{
	glutKeyboardUpFunc(keyboardUpCallBack);
}

/**
 * Setter for special keyboard callback
 * @param  specialFunc special keyboard callback to set
 */
void LIB_API Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
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
 * Function that prints the scene graph
 * @param  scene the scene graph to print
 * @param indentation text intentation
 */
void printTree(Node* scene, std::string indentation)
{
	glm::mat4 mat = scene->getMatrix();
	std::cout << indentation.c_str() << scene->getName().c_str() << std::endl;
	for (int i = 0; i < scene->getChildrenSize(); i++)
		printTree(scene->getChildren().at(i), "\t - " + indentation);
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
 * @param  projection
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
 * Turn on/off lights
 */
void LIB_API Engine::switchLights()
{
	lighting = !lighting;
	enableLighting(lighting);
}

/**
 * Enable / disable illumination
 * @param  value true = enable lights false = disable lights
 */void LIB_API Engine::enableLighting(bool value)
{
	if (value) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}
}

/**
 * Change light state given its name
 * @param  scene scene graph
 * @param2 lightName
 */
void LIB_API Engine::enableLight(Node *scene, std::string lightName)
{
	Light* light = static_cast<Light *>(getNodeByName(scene, lightName));
	if (light != nullptr)
		light->changeState();
}

/**
 * Render some 2D text with various information
 */
void LIB_API Engine::renderText()
{
	char text[64];
	//colore testo
	glColor3f(1.0f, 1.0f, 1.0f);
	strcpy_s(text, "[1, 2, 3] turn on/off lights");
	glRasterPos2f(10.0f, 20.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	glColor3f(1.0f, 1.0f, 1.0f);
	sprintf_s(text, "FPS: %.1f", fps);
	glRasterPos2f(10.0f, 40.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	strcpy_s(text, "[c] change camera");
	glRasterPos2f(10.0f, 60.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	sprintf_s(text, "[r] rotate model ");
	glRasterPos2f(10.0f, 80.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
}

/**
 * Starting from current node it recursively populate the scene graph
 * @param  currentNode the current node
 * @param2 nodes the list of remaining nodes to insert
 */
void LIB_API findChildren(Node* currentNode, std::vector<Node*>& nodes)
{
	const int capacity = currentNode->getCapacity();
	for (int i = 0; i < capacity; i++) {
		Node* next = nodes.at(0);
		nodes.erase(nodes.begin());
		findChildren(next, nodes);
		currentNode->insert(next);
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

	setCameraToPalm(root);

	printTree(root, "");
	return root;
}
//
/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
*/
void LIB_API Engine::setCameraToPalm(Node* root)
{
	Node* palmo = getNodeByName(root, "guardia");
	for (Camera * c : cameras)
		if (c->getMovable())
		{
			glm::vec3 eye = c->getMatrix()[0];
			glm::vec3 center = palmo->getMatrix()[3];
			glm::vec3 up = c->getMatrix()[2];
			c->setMatrix(glm::lookAt(eye, center, up));
			palmo->insert(c);
		}
}

/**
 * takes a node from scene graph searching it by his name
 * @param root node and node name
 */
Node*  Engine::getNodeByName(Node* root, std::string name)
{
	if (root->getName().compare(name) == 0)
		return root;
	else {
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
* read the scene graph and put the nodes in List
* @param initial matrix and root node
*/
void  LIB_API Engine::setRenderList(Node* element)
{
	toRender->add(element);

	std::vector<Node*> children = element->getChildren();

	if (element->getType() == Node::Type::MESH)
	{
		Mesh * mesh = (Mesh *)element;
		if (mesh->getMaterial() != nullptr && mesh->getMaterial()->isTrasparent())
		{
			printf("Aggiungo mesh trasparente %s \n", mesh->getName().c_str());
			trasparentMeshes->add(element);
		}
	}
	for (Node * n : children)
		setRenderList(n);
}

 /**
  * Set render and trasparent lists
  * @param  root scene graph
  */
void LIB_API Engine::setLists(Node * root) {
	//toRender = new List();
	setRenderList(root);
	std::vector<Node*> render = toRender->getList();
	std::vector<Node*> transparent = toRender->getList();
	sortTrasparentMeshesList(transparent);
	toRender->insert(transparent);
}

void LIB_API Engine::setLists(Node * root, glm::mat4 reflection)
{
	//glScalef(1.0, -1.0, 1.0);
	root->setMatrix(root->getFinalMatrix()*reflection);
	Engine::getInstance().setLists(root);
}
/**
 * Render all elements in the list
 */
void LIB_API Engine::renderList() {
	std::vector<Node*> render = toRender->getList();
	for (Node* n : render)
	{
		glm::mat4 renderMatrix = n->getFinalMatrix();
		Object::Type type = n->getType();

		if (type == Object::Type::MESH)
		{
			Mesh* m = static_cast<Mesh*>(n);
			if (m->getMaterial() != nullptr)
			{
				if (m->getMaterial()->isTrasparent()) {
					// TRASPARENZE
					transparentPreRender(m->getMaterial(), renderMatrix);
				}
				else {
					m->getMaterial()->render(renderMatrix);
				}
				m->getMaterial()->getTexture()->render(renderMatrix);
			}
		}
		n->render(currentCamera->getMatrix() * renderMatrix);
	}
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
 * @param  name camera name
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
	// la camera verra settata successivamente, quando la scena verrà caricata.
	if (movable)
		camera->setMatrix(glm::mat3(eye, center, up));//perché questa la setti così?
	else
		camera->setMatrix(glm::lookAt(eye, center, up));
	cameras.push_back(camera);
	// update
	currentCamera = camera;
	activeCamera = static_cast<int>(cameras.size() - 1);
}

/**
* Getter for current camera movable
* @return true if current camera is movable false otherwise
*/
bool LIB_API Engine::isMovableCamera()
{
	return currentCamera->getMovable();
}

void LIB_API Engine::moveCameraX(float direction)
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 mov = direction * glm::vec3(5.0f, 0.0f, 0.0f);
	currentCamera->setMatrix(glm::translate(matrix, mov));
}

void LIB_API Engine::moveCameraY(float direction)
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 mov = direction * glm::vec3(0.0f, 5.0f, 0.0f);
	currentCamera->setMatrix(glm::translate(matrix, mov));
}

void LIB_API Engine::moveCameraZ(float direction)
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 mov = direction * glm::vec3(0.0f, 0.0f, 5.0f);
	currentCamera->setMatrix(glm::translate(matrix, mov));
}

/*
void Engine::moveCamera(float length, glm::vec3 axis) {
	currentCamera->setMatrix(glm::translate(currentCamera->getMatrix(), length*axis));
}
*/

 /**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::changeCamera() {
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
}


/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
*/
void LIB_API Engine::moveCamera(float direction)
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 axis = 0.2f * direction * matrix[2];
	axis[2] *= -1;
	currentCamera->setMatrix(glm::translate(matrix, axis));
	//glm::vec3 eye = currentCamera->getMatrix()[3];
	//glm::vec3 center = glm::vec3(0.0f, -30.0f, 0.0f);
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//currentCamera->setMatrix(glm::lookAt(eye, center, up));
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::rotateModel(Node * root, float angle) {
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		guardia->setMatrix(guardia->getMatrix()*rotation);
	}
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */

void LIB_API Engine::closeThumb(Node *root, float angle) {

	std::string name = fingerNames[0];
	name.append("1");
	Node* finger = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("2");
	Node* finger1 = getNodeByName(root, name);

	//ruota in x e in y
}


/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::closeFinger(Node * root, int i, float  angle)
{
	std::string name = fingerNames[i];
	name.append("1");
	Node* finger = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("2");
	Node* finger1 = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("3");
	Node* finger2 = getNodeByName(root, name);
	glm::mat4 rotationZ;
	//reset position
	if (angle < 0) {
		rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(-fingerAngles[i]), glm::vec3(0.0f, 0.0f, -1.0f));
		fingerAngles[i] = 0;

	}//close the finger
	else {
		if (fingerAngles[i] < 75) {
			rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
			fingerAngles[i] += angle;
		}
	}
	finger->setMatrix(finger->getMatrix()*rotationZ);
	finger1->setMatrix(finger1->getMatrix()*rotationZ);
	finger2->setMatrix(finger2->getMatrix()*rotationZ);
}

/**
 * Close hand
 * @param  root
 * @param angle
 */
void LIB_API Engine::closeHand(Node * root, float  angle)
{
	closeThumb(root, angle);
	closeFinger(root, 1, angle);
	closeFinger(root, 2, angle);
	closeFinger(root, 3, angle);
	closeFinger(root, 4, angle);
}
void LIB_API Engine::free()
{
	//TODO
}

/**
* depth-sorting (back to front) method for transparent meshes
* @param two list element to compare
*/
//TODO:: GREG GUARDA CHE ESISTE LO STENCIL BUFFER PER QUESTO, GUARDA LE SLIDE -> no questo serve leggiti le slide sulle trasparenze. Lo stencil buffer non centra nulla
bool LIB_API listNodeCompare(Node*a, Node *b)
{
	glm::mat4 first = currentCamera->getMatrix() * a->getMatrix();
	glm::mat4 second = currentCamera->getMatrix() * b->getMatrix();
	return (float)first[3].z > (float)second[3].z;
}

/**
* sorts the trasparent meshes list
* @param list of transparent meshes
*/
void LIB_API Engine::sortTrasparentMeshesList(std::vector<Node*> transparentMeshes)
{
	glDepthMask(GL_FALSE);
	//gli passo un comparator
	std::sort(transparentMeshes.begin(), transparentMeshes.end(), listNodeCompare);
	glDepthMask(GL_TRUE);
}
//setta valore alpha ad un nodo specifico
void LIB_API Engine::setAlphaToMaterial(Node * root, float alpha, std::string nodeName)
{
	Node* node = getNodeByName(root, nodeName);
	if (node != nullptr)
	{
		Mesh* mesh = (Mesh*)node;
		mesh->getMaterial()->setAlpha(alpha);
	}
}
/**
* support method for transparent render
* @param material and render matrix
*/
void LIB_API Engine::transparentPreRender(Material *material, glm::mat4 renderMatrix)
{
	glm::mat4 reflection = glm::scale(glm::mat4(), glm::vec3(1.0f, -1.0f, 1.0));

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	// At first render back faces
	glCullFace(GL_FRONT);
	material->render(renderMatrix);
	// Then render front faces
	glCullFace(GL_BACK);
	material->render(renderMatrix);
	// Enabled z-buffer write
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
}
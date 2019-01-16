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
int activeCamera = 1;

List* toRender = new List();

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Engine::~Engine() 
{
	FreeImage_DeInitialise();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::init(int argc, char* argv[]) 
{
	std::cout << "The engine starts" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// setto opzioni finestra
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// creo finestra
	windowId = glutCreateWindow("Engine");
	glewExperimental = GL_TRUE;  // Optional, but recommended
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
	glEnable(GL_NORMALIZE);
	// Init di glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Error loading GLEW
		printf("Error loading GLEW\n");
	}
	if (!glewIsSupported("GL_VERSION_2_1")) {
		// Required OpenGL version not supported
		printf("Required OpenGL version not supported\n");
	}
	enableLighting(true);
	glEnable(GL_LIGHT0);
	enableZbuffer();
	freeImageInitialize();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::startLoop() 
{
	glutMainLoop();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::loadMatrix(glm::mat4 matrix) 
{
	glLoadMatrixf(glm::value_ptr(matrix));
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::clearColor(float r, float g, float b) 
{
	glClearColor(r, g, b, 1.0f);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::mouseWheel(void(*mouseWheelFunc)(int, int, int, int)) 
{
	glutMouseWheelFunc(mouseWheelFunc);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::mousePressed(int button, int state, int x, int y)
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
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::mousePressed(void(*mouseFunc)(int, int, int, int)) 
{
	glutMouseFunc(mouseFunc);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::redisplay() 
{
	glutPostWindowRedisplay(windowId);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::reshape(void(*reshapeCallback)(int, int)) 
{
	glutReshapeFunc(reshapeCallback);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::display(void(*displayCallback)()) 
{
	glutDisplayFunc(displayCallback);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::timer(void callback(int)) 
{
	// calcolo fps -> da completare
	fps = frames / 1.0f;
	frames = 0;
	// Register the next update:
	glutTimerFunc(1000, callback, 0);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int)) 
{
	glutKeyboardFunc(keyboardCallBack);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::setViewport(int x, int y, int width, int height) 
{
	glViewport(x, y, width, height);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::clearBuffers() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::swapBuffers()
{
	glutSwapBuffers();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::loadIdentity()
{
	loadMatrix(glm::mat4(1.0f)); 
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void printTree(Node* node, std::string indentation)
{
	auto mat = node->getMatrix();
	std::cout << indentation.c_str() << node->getName().c_str() << std::endl;
	for (int i = 0; i < node->getChildrenSize(); i++)
		printTree(node->getChildren().at(i), "\t - " + indentation);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::freeImageInitialize() 
{
	FreeImage_Initialise();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::setProjectionMatrix(glm::mat4 projection) 
{
	currentCamera->setProjectionMatrix(projection);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::enableZbuffer() 
{ 
	glEnable(GL_DEPTH_TEST); 
}

// accende / spegne luci
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::switchLights()
{
	lighting = !lighting;
	enableLighting(lighting);
}
//accende / spegne illuminazione
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */void LIB_API Engine::enableLighting(bool value)
{
	if (value) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}
}

//abilita/disabilita una luce dato il suo nome 
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::enableLight(Node *root, std::string lightName)
{
	Light* light = (Light*)getNodeByName(root, lightName);
	if (light != nullptr)
		light->changeState();
}

//TODO scrivere i comandi del guanto / opzioni 
//scrive info su schermo (FPS etc)
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
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

// parte dal nodo corrente  e popola l'albero
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void findChildren(Node* currentNode, std::vector<Node*>& nodes)
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
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node* Engine::getScene(const char* name) 
{
	std::vector<Node*> nodes = OvoReader::readOVOfile(name);
	Node* root = nodes.at(0);
	nodes.erase(nodes.begin());
	findChildren(root, nodes);
	printTree(root, "");
	return root;
}

/**
 * takes a node from scene graph searching it by his name
 * @param root node and node name
 */
 /**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node* Engine::getNodeByName(Node* root, std::string name) 
{
	if (root->getName().compare(name) == 0) {
		return root;
	}
	else {
		if (root->getChildrenSize() > 0) {
			for (int i = 0; i < root->getChildrenSize(); i++) {
				Node* node = getNodeByName(root->getChildren()[i], name);
				if (node) {
					return node;
				}
			}
		}
		return nullptr;
	}
}

/**
* read the scene graph and put the nodes in List
* @param initial matrix and root node
*/

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void  Engine::setRenderList(Node* element)
{
	toRender->add(element);
	std::vector<Node*> children = element->getChildren();
	for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		setRenderList(*it);
	}
}

/**
 * pass the tree and build several list for elements
 * @param root node and base matrix
 */
 /**
  * Comment
  * @param  name1
  * @param2 name2
  * @return what it returns
  */
void Engine::pass(Node* scene) {
	setRenderList(scene);
}

/**
 * render elements from list
 */
 /**
  * Comment
  * @param  name1
  * @param2 name2
  * @return what it returns
  */
void Engine::renderList()
{
	std::list<Node*> render = toRender->getList();
	for (std::list<Node*>::iterator it = render.begin(); it != render.end();
		++it) {
		std::string s = (*it)->getName();
		int size = (*it)->getChildrenSize();
		glm::mat4 renderMatrix = (*it)->getFinalMatrix();
		if ((*it)->getType() == Object::Type::MESH) {
			Mesh* mesh = (Mesh*)(*it);
			if (mesh->getMaterial() != nullptr) {
				mesh->getMaterial()->render(renderMatrix);
				Texture* t = mesh->getMaterial()->getTexture();
				t->render(renderMatrix);
			}
		}
		(*it)->render(currentCamera->getMatrix() * renderMatrix);
	}
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::incrementFrames()
{
	frames++;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::addCamera(std::string name, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	currentCamera = new Camera();
	currentCamera->setName(name);
	currentCamera->setMatrix(glm::lookAt(eye, center, up));
	cameras.push_back(currentCamera);
}

/**
 * change current camera
 */
 /**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::changeCamera() {
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
}

/**
 * moves actual camera
 * @param translation matrix
 */

 /**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::moveCamera(float direction)
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 axis = direction * matrix[2];
	currentCamera->setMatrix(glm::translate(matrix, axis));
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::rotateModel(Node * root, float angle) {
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		guardia->setMatrix(guardia->getMatrix()*rotation);
	}
}
//TODO completare, limitare la rotazione e far si che quando mollo spazio faccia la rotazione inversa (se possibile)
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::closeThumb(Node * root)
{
	Node* finger = getNodeByName(root, "pollice1");
	Node* finger2 = getNodeByName(root, "pollice2");
	//le falangi dovrebbero ruotare anche su un altro asse probabilmente r1*r2 
	glm::mat4 rotationFinger = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationFinger2 = glm::rotate(glm::mat4(1.0f), glm::radians(5.f), glm::vec3(1.0f, 0.0f, 0.0f));
	finger->setMatrix(finger->getMatrix()*rotationFinger);
	finger2->setMatrix(finger2->getMatrix()*rotationFinger2);
}
//TODO completare (settare assi/angoli giusti etc)
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::closeFinger(Node * root, std::string name)
{
	name.append("1");
	Node* finger = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("2");
	Node* finger1 = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("3");
	Node* finger2 = getNodeByName(root, name);

	glm::mat4 rotationFinger = glm::rotate(glm::mat4(1.0f), glm::radians(20.f), glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 rotationFinger1 = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 rotationFinger2 = glm::rotate(glm::mat4(1.0f), glm::radians(5.f), glm::vec3(0.0f, 0.0f, -1.0f));

	finger->setMatrix(finger->getMatrix()*rotationFinger);
	finger1->setMatrix(finger1->getMatrix()*rotationFinger1);
	finger2->setMatrix(finger2->getMatrix()*rotationFinger2);
}

void Engine::closeHand(Node * root)
{
	closeThumb(root);
	closeFinger(root,"indice");
	closeFinger(root,"medio");
	closeFinger(root,"anulare");
	closeFinger(root,"mignolo");
}

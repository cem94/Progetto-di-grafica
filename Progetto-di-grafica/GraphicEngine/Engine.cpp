#include "Engine.h"
#include <GL/glew.h>

//FreeGlut//
#include <GL/freeglut.h>
//FreeImage
#include <FreeImage.h>

/////////////
// GLOBALS //
////////////
int windowId;
//performance properties
float fps = 0.f;
int frames = 0;
//options
bool lighting = true;
//Cameras
Camera *currentCamera = nullptr;
std::vector<Camera*> cameras;
int activeCamera = 1;

//lists
List *toRender = new List();
List *objects = new List();
List *lights = new List();

//init function//
void LIB_API Engine::init(int argc, char *argv[])
{
	std::cout << "The engine starts" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//setto opzioni finestra
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//creo finestra
	windowId = glutCreateWindow("Engine");
	glewExperimental = GL_TRUE; // Optional, but recommended
	//Init di glew
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Error loading GLEW
		printf("Error loading GLEW\n");
	}
	if (!glewIsSupported("GL_VERSION_2_1"))
	{
		// Required OpenGL version not supported
		printf("Required OpenGL version not supported\n");
	}
}

//main loop//
void LIB_API Engine::startLoop() {
	//così posso controllare quando chiuderla p.e premendo un bottone
	/*while (condition) {
		glutMainLoopEvent();
	}*/
	glutMainLoop();
}

//load matrix as current OpenGL matrix
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

//clear the screen 
void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void Engine::mouseWheel(void(*mouseWheelFunc)(int, int, int, int))
{
	glutMouseWheelFunc(mouseWheelFunc);
}

//TODO capire come possiamo usarlo nel nostro progetto
void Engine::mousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{
		//isMousePressed = false;
	}
	if (state == GLUT_DOWN)
	{
		//isMousePressed = true;
		//mousePosition.x = x;
		//mousePosition.y = y;
	}
}

//mousePressedCallback
void Engine::mousePressed(void(*mouseFunc)(int, int, int, int))
{
	glutMouseFunc(mouseFunc);
}

//redisplay window
void LIB_API Engine::redisplay()
{
	glutPostWindowRedisplay(windowId);
}

//reshape callback
void LIB_API Engine::reshape(void(*reshapeCallback)(int, int))
{
	glutReshapeFunc(reshapeCallback);
}

//display callback
void LIB_API Engine::display(void(*displayCallback)())
{
	glutDisplayFunc(displayCallback);
}

void LIB_API Engine::timer(void callback(int))
{
	//calcolo fps -> da completare
	fps = frames / 1.0f;
	frames = 0;
	// Register the next update:
	glutTimerFunc(1000, callback, 0);
}

void LIB_API Engine::keyboard(void(*keyboardCallBack)(unsigned char, int, int))
{
	glutKeyboardFunc(keyboardCallBack);
	//-> non so se serve
	redisplay();
}

void Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
	//-> non so se serve
	redisplay();
}

void LIB_API Engine::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void LIB_API Engine::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::swapBuffers()
{
	glutSwapBuffers();
}

void LIB_API Engine::loadIdentity() {
	loadMatrix(glm::mat4(1.0f));
}

void printTree(Node *node, std::string indentation) {
	auto mat = node->getMatrix();
  std::cout << indentation.c_str() << node->getName().c_str()<< std::endl;
	for (int i = 0; i < node->getChildrenSize(); i++)
		printTree(node->getChildren().at(i), "\t - " + indentation);
}

void Engine::freeImageInitialize()
{
	FreeImage_Initialise();
}

void Engine::freeImageDeInitialize()
{
	FreeImage_DeInitialise();
}

void LIB_API Engine::setProjectionMatrix(glm::mat4 projection)
{
	currentCamera->setProjectionMatrix(projection);
}

void LIB_API Engine::enableZbuffer()
{
	glEnable(GL_DEPTH_TEST);
}

//accende / spegne luci
void Engine::switchLights()
{
	printf("Lights %d\n", lighting);
	
	lighting = !lighting;
	enableLighting(lighting);
}
void Engine::enableLighting(bool value)
{
	if(value)
	glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}
//abilita/disabilita l'illuminazione(per renderizzare in 2D (testo etc)
void LIB_API Engine::enableLight(Node *root, std::string lightName)
{
	Light* light = (Light*)getNodeByName(root, lightName);
	if (light != nullptr)
		light->changeState();
	else
		std::cout << "Light not present" << std::endl;
}

//scrive info su schermo (FPS etc)
void LIB_API Engine::renderText()
{
	if (lighting)
		enableLighting(false);
	//TODO scrivere i comandi del guanto / opzioni / fps
	char text[64];
	//colore testo
	glColor3f(1.0f, 1.0f, 1.0f);
	if (lighting)
		strcpy_s(text, "Lighting on");
	else
		strcpy_s(text, "Lighting off");
	glRasterPos2f(10.0f, 20.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	glColor3f(1.0f, 1.0f, 1.0f);
	sprintf_s(text, "FPS: %.1f", fps);
	glRasterPos2f(10.0f, 40.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	strcpy_s(text, "[c] change camera");
	glRasterPos2f(10.0f, 60.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	//---------------------------------------------------------------------
	if (lighting)
		enableLighting(true);
}

//parte dal nodo corrente  e popola l'albero
void findChildren(Node* currentNode, std::vector<Node*>& nodes) {
	const int capacity = currentNode->getCapacity();
	for (int i = 0; i < capacity; i++) {
		Node * next = nodes.at(0);
		nodes.erase(nodes.begin());
		findChildren(next, nodes);
		currentNode->insert(next);
	}
}

Node * Engine::getScene(const char * name)
{
	std::vector<Node*> nodes = OvoReader::readOVOfile(name);
	Node* root = nodes.at(0);
	nodes.erase(nodes.begin());
	findChildren(root, nodes);
	//printTree(root, "");
	return root;
}

/**
* takes a node from scene graph searching it by his name
* @param root node and node name
*/
Node * Engine::getNodeByName(Node * root, std::string name)
{
	if (root->getName().compare(name) == 0)
	{
		return root;
	}
	else
	{
		if (root->getChildrenSize() > 0)
		{
			for (int i = 0; i < root->getChildrenSize(); i++)
			{
				Node *node = getNodeByName(root->getChildren()[i], name);
				if (node)
				{
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
void  Engine::populateListFromTree(glm::mat4 fatherMatrix, Node* root)
{
	std::vector<Node*> children = root->getChildren();
	glm::mat4 actualMatrix = root->getFinalMatrix();
	root->setMatrix(root->getFinalMatrix());

	switch (root->getType()) {
	case Object::Type::NODE:
		objects->add(root);
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
		break;
	case Object::Type::MESH:
		objects->add((Mesh*)root);
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
		break;
	case Object::Type::LIGHT:
		lights->add(root);
		std::vector<Node*> children = root->getChildren();
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
		break;
	}
}

/**
* pass the tree and build several list for elements
* @param root node and base matrix
*/
void Engine::pass(Node* root, glm::mat4 baseMatrix)
{
	toRender = new List();
	populateListFromTree(baseMatrix, root);
	printf("Lights %d \n", lights->getList().size());
	toRender->insert(lights->getList());
	printf("Objects %d \n", objects->getList().size());
	toRender->insert(objects->getList());
}

/** 
* render elements from list
*/
void  Engine::renderList()
{
	//toRender->render(glm::mat4(1.0f));
	std::list<Node*> render = toRender->getList();
	for (std::list<Node*>::iterator it = render.begin(); it != render.end(); ++it)
	{
		glm::mat4 renderMatrix = (*it)->getMatrix();
		if ((*it)->getType() == Object::Type::MESH)
		{
			Mesh* mesh = (Mesh*)(*it);
			if (mesh->getMaterial() != nullptr)
			{
				//renderizzo materiale mesh
				mesh->getMaterial()->render(renderMatrix);
				//renderizzo textures mesh TODO
				Texture* t = mesh->getMaterial()->getTexture();
					t->render(renderMatrix);
			}
		}
		//renderizzo elementi
		std::string s = (*it)->getName();

		(*it)->render(currentCamera->getMatrix()*renderMatrix);
	}
	//svuoto le liste -> perché??
	objects = new List();
	lights = new List();
}

void Engine::incrementFrames(){	frames++;}

Camera * Engine::addCamera(std::string name, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera * camera = new Camera();
	printf("Id: %d\n",camera->getId());
	camera->setName(name);
	camera->setProjectionMatrix(glm::lookAt(eye, center, up));
	//aggiunge la camera all'elenco
	cameras.push_back(camera);
	//e la setta come camera corrente
	currentCamera = camera;
	return currentCamera;
}

/**
* change current camera
*/
void Engine::changeCamera()
{
	printf("Changing camera from %s ", currentCamera->getName().c_str());
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
	printf("to %s\n", currentCamera->getName().c_str());
}

/**
* moves actual camera
* @param translation matrix
*/
void Engine::moveCamera(glm::vec3 translation)
{
	currentCamera->setMatrix(glm::translate(currentCamera->getMatrix(), translation));
}

/**
* set a specific camera to gauntlet
* @param root node and camera name
*/
void Engine::setCameraToNode(Node* root, std::string cameraName, std::string nodeName)
{
	//ottengo il nodo cercato
	Node* gauntlet = getNodeByName(root, nodeName);
	Camera* camera = nullptr;
	if (gauntlet != nullptr)
	{
		for (std::vector<Camera*>::iterator it = cameras.begin(); it != cameras.end(); ++it)
		{
			if ((*it)->getName().compare(cameraName) == 0)
			{
				camera = *it;
			}
		}
		if (camera != nullptr)
		{
			root->remove(camera);
			glm::vec3 pos = gauntlet->getMatrix()[3];
			glm::vec3 eye = glm::vec3(pos.x, pos.y + 50, pos.z - 400);
			glm::vec3 center = pos;
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			camera->setMatrix(glm::lookAt(eye, center, up));
			gauntlet->insert(camera);
		}
	}
}
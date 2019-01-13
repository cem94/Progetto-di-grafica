#include "Engine.h"
#include "OvoReader.h"
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
bool wireframe = false;
bool lighting = true;
//Cameras
Camera *currentCamera = nullptr;
std::vector<Camera*> cameras;
int activeCamera = 0;
//lists
List *renderList = new List();
List *listObjects = new List();
List *listLight = new List();

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
	frames++;//TODO completare e testare
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
	//redisplay(); -> non so se serve
}

void Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
	//	redisplay();
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

void print(std::vector<Node*> nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		std::cout << nodes.at(i)->getName().c_str() << std::endl;
	}
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
	lighting = !lighting;
	enableLighting(lighting);
}

//abilita/disabilita l'illuminazione(per renderizzare in 2D (testo etc)
void LIB_API Engine::enableLighting(bool value)
{
	if (value) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
}

//scrive info su schermo (FPS etc)
void LIB_API Engine::renderText()
{
	if (lighting)
		enableLighting(false);
	//TODO scrivere i comandi del guanto / opzioni / fps
	char text[64];
	//cambiato da strcpy il compilatore dice che è più sicuro strcpy_s
	if (wireframe)
		strcpy_s(text, "Wireframe on");
	else
		strcpy_s(text, "Wireframe off");
	//colore testo
	glColor3f(0.0f, 1.0f, 1.0f);
	//x,y del testo 
	glRasterPos2f(10.0f, 20.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	if (lighting)
		strcpy_s(text, "Lighting on");
	else
		strcpy_s(text, "Lighting off");
	glRasterPos2f(10.0f, 40.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	strcpy_s(text, "Some text3");
	glRasterPos2f(10.0f, 60.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	if (lighting)
		enableLighting(true);
}

void LIB_API Engine::switchWireframe()
{
	wireframe = !wireframe;
	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LIB_API Engine::setRandomColors()
{
	glm::vec4 color((rand() % 100) / 100.0f,
		(rand() % 100) / 100.0f,
		(rand() % 100) / 100.0f,
		1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(color));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(color));
}

//parte dal nodo corrente  e popola l'albero
void findChildren(Node* currentNode, std::vector<Node*>& nodes) {
	for (int i = 0; i < currentNode->getChildrenSize(); i++) {
		//prendo elemento dalla lista (rimuovendolo)
		Node * temp = nodes.at(0);
		nodes.erase(nodes.begin());
		//e scendo
		findChildren(temp, nodes);
		//lo inserisco come figlio del nodo corrente
		currentNode->insert(temp);
	}
}

Node * Engine::getRoot(const char * name)
{
	std::vector<Object*> objects = OvoReader::readOVOfile(name);
	//cast della lista da Object* a Node*
	std::vector<Node*> nodes{};
	for (auto o : objects) {
		nodes.push_back(dynamic_cast<Node*>(o));
	}
	//prendo la testa come root
	Node* root = nodes.at(0);
	// e la cancello
	nodes.erase(nodes.begin());
	findChildren(root, nodes);
	printTree(root, "");
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
				Node *tmpNode = getNodeByName(root->getChildren()[i], name);
				if (tmpNode)
				{
					return tmpNode;
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
	///////////////////////////////////////////////////////////////////////////////////////////
	/*glm::mat4 actualMatrix = fatherMatrix * root->getMatrix();
	std::vector<Node*> children = root->getChildren();
	Mesh* mesh = nullptr;
	switch (root->getType()) {
	case Object::Type::NODE:
		listObjects->add(root, actualMatrix);
		break;
	case Object::Type::MESH:
		mesh = (Mesh*)root;
		//forse il bug che non trovavano
		listObjects->add(root, actualMatrix);
		break;
	case Object::Type::LIGHT:
		listLight->add(root, actualMatrix);
		break;
	default:
	//	printf("Error type not managed \n");
		//exit(0);
		break;
	}
	for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		populateListFromTree(actualMatrix, *it);
	}*/
	///////////////////////////////////////////////////////////////////////////////////////////
	if (root->getType() == Object::Type::NODE)
	{
		glm::mat4 actualMatrix = fatherMatrix * root->getMatrix();
		listObjects->add(root, actualMatrix);
		std::vector<Node*> children = root->getChildren();
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
	}
	else if (root->getType() == Object::Type::MESH)
	{
		glm::mat4 actualMatrix = fatherMatrix * root->getMatrix();
		Mesh* mesh = (Mesh*)root;
		listObjects->add(root, actualMatrix);
		std::vector<Node*> children = root->getChildren();
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
	}
	else if (root->getType() == Object::Type::LIGHT)
	{
		glm::mat4 actualMatrix = fatherMatrix * root->getMatrix();
		listLight->add(root, actualMatrix);
		std::vector<Node*> children = root->getChildren();
		for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			populateListFromTree(actualMatrix, *it);
		}
	}
}

/**
* pass the tree and build several list for elements
* @param root node and base matrix
*/
void Engine::pass(Node* root, glm::mat4 baseMatrix)
{
	renderList = new List();
	populateListFromTree(baseMatrix, root);
	std::list<Node*> render;
	std::list<Node*> renderLight = listLight->getList();
	std::list<Node*> renderNode = listObjects->getList();

	if (renderLight.size() > 0)
	{
		render.insert(render.begin(), renderLight.begin(), renderLight.end());
	}
	if (renderNode.size() > 0)
	{
		render.insert(render.end(), renderNode.begin(), renderNode.end());
	}
	renderList->setList(render);
}

/** TODO spostare in list.render
* render elements from list
*/
void  Engine::renderElementsList()
{
	std::list<Node*> render = renderList->getList();
	if (render.size() == 0) { printf("Render list empty\n"); }
	else {
		printf("Rendering list of %d elements \n",render.size());
	}
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
				//renderizzo textures mesh
				mesh->getMaterial()->getTexture()->render(renderMatrix);
			}
		}
		//renderizzo elementi
		(*it)->render(currentCamera->getMatrix()*renderMatrix);
	}
	//svuoto le liste -> perché??
	listObjects = new List();
	listLight = new List();
}

void Engine::incrementFrames()
{
	frames++;
}

Camera * Engine::addCamera(std::string name, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera * camera = new Camera();
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
	printf("Changing camera \n");
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
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
			glm::vec3 eye = glm::vec3(pos.x, pos.y + 50, pos.z - 100);
			glm::vec3 center = pos;
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			camera->setMatrix(glm::lookAt(eye, center, up));
			gauntlet->insert(camera);
		}
	}
}



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
float totalAngle = 0.f;
float totalAngleZ = 0.0f;
float fingerAngles[5];
// per il pollice
float angleX;
std::string fingerNames[5] = {"pollice", "indice", "medio", "anulare", "mignolo"};

// Gauntlet translate
bool translateUp = false;
int translateCnt = 0;

// Windows size
int sizeX = 0;
int sizeY = 0;

List* toRender = new List();
List *trasparentMeshes = new List();

//istanza statica definita in Engine.h
Engine* Engine::instance = nullptr;
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

Engine & Engine::getInstance()
{
	if (instance == nullptr)
		instance = new Engine{};
	return *instance;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::init(int argc, char* argv[])
{
	freeImageInitialize();
	std::cout << "The engine starts" << std::endl;
    // setto opzioni finestra
    glutInitWindowSize(1920, 1080);

	//updateSize();

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
	// abilita la trasparenza
	// TODO:: GREG ho visto che abilitano questo, è giusto?
    glEnable(GL_BLEND);
	// (A * S) + (B * D)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	enableZbuffer();
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
void Engine::updateSize() 
{
  sizeY = glutGet(GLUT_WINDOW_WIDTH);
  sizeX = glutGet(GLUT_WINDOW_HEIGHT);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int Engine::getWindowSizeX() 
{
	return sizeX; 
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int Engine::getWindowSizeY() 
{
	return sizeY; 
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::mouseMoved(void (*mouseMoved)(int, int)) 
{
  glutPassiveMotionFunc(mouseMoved);
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
	glm::mat4 mat = node->getMatrix();
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
	Light* light = static_cast<Light *>(getNodeByName(root, lightName));
	if (light != nullptr)
		light->changeState();
}

//TODO scrivere i comandi del guanto / opzioni 
//scrive info su schermo (FPS etc)
//TODO:: il colore !!
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
   
	setCameraToPalm(root);

	printTree(root, "");
	return root;
}

 /**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::setCameraToPalm(Node* root) 
{
	Node* palmo = getNodeByName(root, "guardia");
	for (Node* n : palmo->getChildren()) {
		if (n->getType() == Object::Type::CAMERA) 
		{
            n = currentCamera;
			return;
		}
	}
	palmo->insert(currentCamera);
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
	if (root->getName().compare(name) == 0)
		return root;
	else{
          for (Node* n : root->getChildren()) 
		  {
			  Node* founded = getNodeByName(n, name);
			  if (founded!= nullptr) 
				  return founded;
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

	if (element->getType() == Node::Type::MESH) 
	{
		Mesh * mesh = (Mesh *)element;
		if (mesh->getMaterial() != nullptr && mesh->getMaterial()->isTrasparent())
		{
			printf("Aggiungo mesh trasparente %s \n", mesh->getName().c_str());
			trasparentMeshes->add(element);
		}
	}
    for (Node * n: children)
		setRenderList(n);
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
  //Temporanea per testare trasparenze
void Engine::setLists(Node * root) {
	setRenderList(root);
	std::vector<Node*> render = toRender->getList();
	std::vector<Node*> transparent = toRender->getList();
	sortTrasparentMeshesList(transparent);
	render.insert(render.end(), transparent.begin(), transparent.end());
}

void Engine::setLists(Node * root, glm::mat4 reflection)
{
	//glScalef(1.0, -1.0, 1.0);
	//root->setMatrix(root->getFinalMatrix()*reflection);
	Engine::getInstance().setLists(root);
}

void Engine::renderList() { 
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
              } else {
                m->getMaterial()->render(renderMatrix);
              }
              m->getMaterial()->getTexture()->render(renderMatrix);
            }
        }
		n->render(currentCamera->getMatrix() * renderMatrix);
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
void Engine::addCamera(std::string name, bool movable, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera* camera = new Camera();
	camera->setName(name);
	camera->setMovable(movable);
	camera->setType(Object::Type::CAMERA);

	camera->setMatrix(glm::lookAt(eye, center, up));
    cameras.push_back(camera);
	// update
    currentCamera = camera;
    activeCamera =static_cast<int>(cameras.size() - 1);
}

/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
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
	glm::vec3 mov = direction * glm::vec3(0.0f, 3.0f, 0.0f);
	currentCamera->setMatrix(glm::translate(matrix, mov));
}

void LIB_API Engine::moveCameraZ(float direction) 
{
	glm::mat4 matrix = currentCamera->getMatrix();
	glm::vec3 mov = direction * glm::vec3(0.0f, 0.0f, 5.0f);
	currentCamera->setMatrix(glm::translate(matrix, mov));
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
void Engine::changeCamera(Node * root) {
	activeCamera = (activeCamera + 1) % cameras.size();
	currentCamera = cameras.at(activeCamera);
    setCameraToPalm(root);
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
	//axis[2] *= -1;
	currentCamera->setMatrix(matrix * glm::translate(glm::mat4(1.0f), axis));
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

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::autoRotateModel(Node* root, float angle) {
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr) {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 translate;
        translateCnt++;
		if (translateUp) 
			translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
		else 
			translate =	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

		guardia->setMatrix(guardia->getMatrix() * translate * rotation);

        if (translateCnt > 180) {
			translateCnt = 0;
			translateUp = !translateUp;
		}
  }
}



//TODO completare risolvere l'errore nel pollice
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::closeFinger(Node * root, int i, float  angle)
{	
	std::string name = fingerNames[i];
	name.append("1");
	Node* finger = getNodeByName(root, name);
	name = name.substr(0, name.size() - 1);
	name.append("2");
	Node* finger1 = getNodeByName(root, name);
	Node* finger2 = nullptr;
	if (i > 0) {
		//non pollice
		name = name.substr(0, name.size() - 1);
		name.append("3");
		Node* finger2 = getNodeByName(root, name);
	}
	glm::mat4 rotationZ;
	//così non ruota le altre dita
	glm::mat4 rotationX(1.0f);
	//reset position
	if (angle < 0) {
		printf("Moving the hand back of %lf\n", -fingerAngles[i]);
		rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(-fingerAngles[i]), glm::vec3(0.0f, 0.0f, -1.0f));
		fingerAngles[i] = 0;
		if (i == 0) {
			printf("Resetting thumb. Current angleX %lf \n", angleX);
			rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(1.0f, 0.0f, 0.0f));
			angleX = 0;
		};
	}//close the finger
	else {
		//bug nel pollice
		if (fingerAngles[i] < 75 && angleX < 35) {
			rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
			if (i == 0) {
			//pollice
				rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
				angleX += angle;
			}
			fingerAngles[i] += angle;
		}
	}
	finger->setMatrix(finger->getMatrix()*rotationZ*rotationX);
	finger1->setMatrix(finger1->getMatrix()*rotationZ*rotationX);
	if(finger2!=nullptr)
	finger2->setMatrix(finger2->getMatrix()*rotationZ);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Engine::closeHand(Node * root, float  angle)
{
		closeFinger(root,0, angle);
		closeFinger(root, 1, angle);
		closeFinger(root, 2, angle);
		closeFinger(root, 3, angle);
		closeFinger(root, 4, angle);
}

void Engine::free()
{
	//TODO
}

/**
* depth-sorting (back to front) method for transparent meshes
* @param two list element to compare
*/
bool listNodeCompare(Node*a, Node *b)
{
	glm::mat4 first = currentCamera->getMatrix() * a->getMatrix();
	glm::mat4 second = currentCamera->getMatrix() * b->getMatrix();
	return (float)first[3].z > (float)second[3].z;
}

/**
* sorts the trasparent meshes list
* @param list of transparent meshes
*/
void Engine::sortTrasparentMeshesList(std::vector<Node*> transparentMeshes)
{
	glDepthMask(GL_FALSE);
	//gli passo un comparator
	std::sort(transparentMeshes.begin(), transparentMeshes.end(), listNodeCompare);
	glDepthMask(GL_TRUE);
}

//setta valore alpha ad un nodo specifico
void Engine::setAlphaToMaterial(Node * root, float alpha, std::string nodeName)
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
void Engine::transparentPreRender(Material *material, glm::mat4 renderMatrix)
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
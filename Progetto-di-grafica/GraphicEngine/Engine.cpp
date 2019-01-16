#include "Engine.h"
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

// lists
List* toRender = new List();
List* objects = new List();
List* lights = new List();
glm::vec3 center;

Engine::~Engine() { FreeImage_DeInitialise(); }


//TODO:: devo vedre come farlo
void Engine::setGuardiaMatrix(Node* root) 
{
	Node* guardia = getNodeByName(root, "guardia");

	center = guardia->getMatrix()[0];
    /* TODO:: REMOVE IT
	  auto stp = guardia->getMatrix();
        std::cout << stp[0][0] << ", " << stp[0][1] << ", " << stp[0][2] << ", "
                  << stp[0][3] << " - " << stp[1][0] << ", " << stp[1][1]
                  << ", " << stp[1][2] << ", " << stp[1][3] << " - "
                  << stp[2][0] << ", " << stp[2][1] << ", " << stp[2][2] << ", "
                  << stp[0][3] << std::endl;
                                  */
}

// init function//
void LIB_API Engine::init(int argc, char* argv[]) {
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
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

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

  // forse si possono spostare in init
  enableZbuffer();
  freeImageInitialize();
}

// main loop//
void LIB_API Engine::startLoop() {
  // cos? posso controllare quando chiuderla p.e premendo un bottone
  /*while (condition) {
          glutMainLoopEvent();
  }*/
  glutMainLoop();
}

// load matrix as current OpenGL matrix
void LIB_API Engine::loadMatrix(glm::mat4 matrix) {
  glLoadMatrixf(glm::value_ptr(matrix));
}

// clear the screen
void LIB_API Engine::clearColor(float r, float g, float b) {
  glClearColor(r, g, b, 1.0f);
}

void Engine::mouseWheel(void (*mouseWheelFunc)(int, int, int, int)) {
  glutMouseWheelFunc(mouseWheelFunc);
}

// TODO capire come possiamo usarlo nel nostro progetto
void Engine::mousePressed(int button, int state, int x, int y) {
  if (state == GLUT_UP) {
    // isMousePressed = false;
  }
  if (state == GLUT_DOWN) {
    // isMousePressed = true;
    // mousePosition.x = x;
    // mousePosition.y = y;
  }
}

// mousePressedCallback
void Engine::mousePressed(void (*mouseFunc)(int, int, int, int)) {
  glutMouseFunc(mouseFunc);
}

// redisplay window
void LIB_API Engine::redisplay() { glutPostWindowRedisplay(windowId); }

// reshape callback
void LIB_API Engine::reshape(void (*reshapeCallback)(int, int)) {
  glutReshapeFunc(reshapeCallback);
}

// display callback
void LIB_API Engine::display(void (*displayCallback)()) {
  glutDisplayFunc(displayCallback);
}

void LIB_API Engine::timer(void callback(int)) {
  // calcolo fps -> da completare
  fps = frames / 1.0f;
  frames = 0;
  // Register the next update:
  glutTimerFunc(1000, callback, 0);
}

void LIB_API Engine::keyboard(void (*keyboardCallBack)(unsigned char, int,
                                                       int)) {
  glutKeyboardFunc(keyboardCallBack);
  //-> non so se serve
  redisplay();
}

void Engine::specialKeyboard(void(*specialFunc)(int, int, int))
{
	glutSpecialFunc(specialFunc);
	redisplay();
}

void LIB_API Engine::setViewport(int x, int y, int width, int height) {
  glViewport(x, y, width, height);
}

void LIB_API Engine::clearBuffers() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LIB_API Engine::swapBuffers() { glutSwapBuffers(); }

void LIB_API Engine::loadIdentity() { loadMatrix(glm::mat4(1.0f)); }

void printTree(Node* node, std::string indentation) {
  auto mat = node->getMatrix();
  std::cout << indentation.c_str() << node->getName().c_str() << std::endl;
  for (int i = 0; i < node->getChildrenSize(); i++)
    printTree(node->getChildren().at(i), "\t - " + indentation);
}

void Engine::freeImageInitialize() { FreeImage_Initialise(); }

void LIB_API Engine::setProjectionMatrix(glm::mat4 projection) {
  currentCamera->setProjectionMatrix(projection);
}

void LIB_API Engine::enableZbuffer() { glEnable(GL_DEPTH_TEST); }

// accende / spegne luci
void LIB_API Engine::switchLights() {
  lighting = !lighting;
  enableLighting(lighting);
}
//spostare in light la parte che accende le luci
void LIB_API Engine::enableLighting(bool value)
{
	if (value) {
		
		glEnable(GL_LIGHTING);
		//sostituire con light->getLightNumber()
		glEnable(GL_LIGHT0);
		//
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
}

//abilita/disabilita l'illuminazione(per renderizzare in 2D (testo etc)
void LIB_API Engine::enableLight(Node *root, std::string lightName)
{
	Light* light = (Light*)getNodeByName(root, lightName);
	if (light != nullptr)
		printf("Found\n");
	//TODO	
	//light->changeState();
	else
		std::cout << "Light not present" << std::endl;
}


//scrive info su schermo (FPS etc)
void LIB_API Engine::renderText()
{
	if (lighting)
		enableLighting(false);

	//TODO scrivere i comandi del guanto / opzioni 
	char text[64];
	//colore testo
	glColor3f(1.0f, 1.0f, 1.0f);
	if (lighting)
		strcpy_s(text, "[l] lighting (on)");
	else
		strcpy_s(text, "[l] lighting (off)");
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
	//---------------------------------------------------------------------
	if (lighting)
		enableLighting(true);
}

// parte dal nodo corrente  e popola l'albero
void findChildren(Node* currentNode, std::vector<Node*>& nodes) {
  const int capacity = currentNode->getCapacity();
  for (int i = 0; i < capacity; i++) {
    Node* next = nodes.at(0);
    nodes.erase(nodes.begin());
    findChildren(next, nodes);
    currentNode->insert(next);
  }
}

Node* Engine::getScene(const char* name) {
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
Node* Engine::getNodeByName(Node* root, std::string name) {
  if (root->getName().compare(name) == 0) {
    return root;
  } else {
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
void  Engine::createLists( Node* element)
{

	if (element->getType() == Object::Type::NODE)
	{
		objects->add(element);
	}
	else if (element->getType() == Object::Type::MESH)
	{
		objects->add(element);
	}
	else if (element->getType() == Object::Type::LIGHT)
	{
		
		lights->add(element);
	}
	else {
	//Camera
		return;
	}
	std::vector<Node*> children = element->getChildren();
	for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		createLists(*it);
	}

}

/**
 * pass the tree and build several list for elements
 * @param root node and base matrix
 */
// TODO capire perch? c'? lista luci
void Engine::pass(Node* scene) {
  toRender = new List();
  createLists(scene);
  // Perch? sono in una lista separata??
  toRender->insert(lights->getList());
  toRender->insert(objects->getList());
}

/**
 * render elements from list
 */
void Engine::renderList() {
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
    // renderizzo elementi
    (*it)->render(currentCamera->getMatrix() * renderMatrix);
  }
  // svuoto le liste -> perch???
  objects = new List();
  lights = new List();
}

void Engine::incrementFrames() { frames++; }

Camera* Engine::addCamera(std::string name, glm::vec3 eye, glm::vec3 center,
                          glm::vec3 up) {
  Camera* camera = new Camera();
  camera->setName(name);
  camera->setMatrix(glm::lookAt(eye, center, up));
  cameras.push_back(camera);
  currentCamera = camera;
  return currentCamera;
}

/**
 * change current camera
 */
void Engine::changeCamera() {
  printf("Changing camera from %s ", currentCamera->getName().c_str());
  activeCamera = (activeCamera + 1) % cameras.size();
  currentCamera = cameras.at(activeCamera);
  setCameraToNode(currentCamera, currentCamera->getName(), "guardia");
  printf("to %s\n", currentCamera->getName().c_str());
}

/**
 * moves actual camera
 * @param translation matrix
 */
void LIB_API Engine::moveCamera(float direction) {
  const glm::mat4 mat_current_camera = currentCamera->getMatrix();
  glm::vec3  tmp = mat_current_camera[2];
  tmp[2] *= -1;
  glm::vec3 z = direction * 3.0f * mat_current_camera[2];
  currentCamera->setMatrix(
      glm::translate(currentCamera->getMatrix(), z));
}

/**
 * set a specific camera to gauntlet
 * @param root node and camera name
 */

void setCameraToGuardia(Node * root, std::string cameraName, std::string nodeName) {
	Node * 
}


void Engine::setCameraToNode(Node* root, std::string cameraName,
                             std::string nodeName) {
  // ottengo il nodo cercato
  Node* searched = getNodeByName(root, nodeName);
  Camera* camera = nullptr;
  if (searched != nullptr) {
    for (std::vector<Camera*>::iterator it = cameras.begin();
         it != cameras.end(); ++it) {
      if ((*it)->getName().compare(cameraName) == 0) {
        camera = *it;
      }
    }
    if (camera != nullptr) {
      root->remove(camera);
      glm::vec3 pos = searched->getMatrix()[3];
      glm::vec3 eye = glm::vec3(pos.x, pos.y + 100, pos.z -200);
      glm::vec3 center = pos;
      glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
      camera->setMatrix(glm::lookAt(eye, center, up));
      searched->insert(camera);
    }
  }
}


void Engine::rotateModel(Node * root, float angle) {
	Node* guardia = getNodeByName(root, "guardia");
	if (guardia != nullptr)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		guardia->setMatrix(guardia->getMatrix()*rotation);
	}
	else {
		printf("Node not found\n");
	}
}
//TODO completare, limitare la rotazione e far si che quando mollo spazio faccia la rotazione inversa (se possibile)
void Engine::closeThumb(Node * root)
{
	Node* finger = getNodeByName(root, "pollice1");
	Node* finger2 = getNodeByName(root, "pollice2");
	//la gemma non segue il dito capire come fare
	Node* gemma= getNodeByName(root, "gemma_pollice");
	glm::mat4 rotationJewel= glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(1.0f, 0.0f, 0.0f));
	//le falangi dovrebbero ruotare anche su un altro asse probabilmente r1*r2 
	glm::mat4 rotationFinger = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationFinger2 = glm::rotate(glm::mat4(1.0f), glm::radians(5.f), glm::vec3(1.0f, 0.0f, 0.0f));
	gemma->setMatrix(gemma->getMatrix()*rotationJewel);
	finger->setMatrix(finger->getMatrix()*rotationFinger);
	finger2->setMatrix(finger2->getMatrix()*rotationFinger2);
}
//TODO completare (settare assi/angoli giusti etc)
void Engine::closeFinger(Node * root,std::string name)
{
	name.append("1");
	Node* finger = getNodeByName(root, name);
	name = name.substr(0,name.size()-1);
	name.append("2");
	Node* finger1 = getNodeByName(root, name);
	Node* finger2 = getNodeByName(root, name);

	glm::mat4 rotationFinger = glm::rotate(glm::mat4(1.0f), glm::radians(20.f), glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 rotationFinger1 = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 rotationFinger2 = glm::rotate(glm::mat4(1.0f), glm::radians(5.f), glm::vec3(0.0f, 0.0f, -1.0f));

	finger->setMatrix(finger->getMatrix()*rotationFinger);
	finger1->setMatrix(finger1->getMatrix()*rotationFinger1);
	finger2->setMatrix(finger2->getMatrix()*rotationFinger2);
}
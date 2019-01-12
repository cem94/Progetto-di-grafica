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
float fps = 0.f;
int frames = 0;
float angleX = 0.0f;
//options
bool wireframe = false;
bool lighting = true;
//Cameras
Camera *currentCamera = nullptr;
std::vector<Camera*> cameras;
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

void LIB_API Engine::startLoop() {
	//così posso controllare quando chiuderla p.e premendo un bottone
	/*while (condition) {
		glutMainLoopEvent();
	}*/
	glutMainLoop();
}
void LIB_API Engine::loadMatrix(glm::mat4 matrix)
{
	glLoadMatrixf(glm::value_ptr(matrix));
}

void LIB_API Engine::clearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void LIB_API Engine::loadFile()
{
	//TODO
}

void LIB_API Engine::redisplay()
{
	glutPostWindowRedisplay(windowId);
	frames++;//TODO completare e testare
}

void LIB_API Engine::reshape(void(*reshapeCallback)(int, int))
{
	glutReshapeFunc(reshapeCallback);
}

void LIB_API Engine::display(void(*displayCallback)())
{
	glutDisplayFunc(displayCallback);
}

void LIB_API Engine::timer(void callback(int))
{
	//calcolo fps -> da completare
	fps = frames / 1.0f;
	frames = 0;
	glutTimerFunc(1000, callback, 0);
	std::cout << fps << std::endl;
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
//usata solo per testare se luci/texture etc funzionanos
void LIB_API Engine::displayScene()
{

	/*glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -45.0f));
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 f = translation * rotation;
	//impostazioni luce
	glm::vec4 ambient(100, 0, 1, 0);
	glm::vec4 diffuse(0, 1, 0, 1);
	glm::vec4 specular(1, 0, 0, 0.5f);
	Light* l = new Light();
	l->setAmbient(ambient);
	l->setDiffuse(diffuse);
	l->setSpecular(specular);
	//render della luce
	l->render(f);
	//aggiungo un po' di elementi
	glColor3f(0.8f, 0.2f, 0.1f);
	glutSolidTeacup(5);
	glColor3f(0.8f, 1.0f, 0.1f);
	glTranslated(30, 0, -30);
	glutSolidTeapot(10);*/

}
void LIB_API Engine::loadIdentity() {
	loadMatrix(glm::mat4(1.0f));
}
void print(std::vector<Node*> nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		std::cout << nodes.at(i)->getName().c_str() << std::endl;
	}
}

//parte dal nodo corrente  e popola l'albero
void findChildren(Node* currentNode, std::vector<Node*>& nodes) {
	//int size = currentNode->getChildrenSize();
	//std::cout << currentNode->getName().c_str() << " children: " << size << std::endl;

		for (int i = 0; i < currentNode->getChildrenSize(); i++) {
		//prendo testa 
		if (nodes.size() == 0) {
			std::cout << " Empty " << std::endl;
		//problema
		}
		Node * temp = nodes.at(0);
		//la tolgo dalla lista
		nodes.erase(nodes.begin());
	//	std::cout << "node  " << temp->getName().c_str() << " children: " << temp->getChildrenSize() << std::endl;
		//e scendo
		findChildren(temp, nodes);
		currentNode->insert(temp);
	}
}

void printTree(Node *node, std::string indentation) {
	auto mat = node->getMatrix();
  std::cout << indentation.c_str() << node->getName().c_str()<< std::endl;
	for (int i = 0; i < node->getChildrenSize(); i++)
		printTree(node->getChildren().at(i), "\t - " + indentation);
}


Node * Engine::readOVOfile(const char * name)
{
	std::vector<Object*> objects = OvoReader::readOVOfile(name);
	//cast della lista da Object* a Node*
	std::vector<Node*> vec{};

	for (auto o : objects) {
		vec.push_back(dynamic_cast<Node*>(o));
	}

	//prendo la testa come root
	Node* root = vec.at(0);
	// e la cancello
	vec.erase(vec.begin());
	//ci attacco i figli per costruire l'albero
	//questo secondo cast non lo capisco 
	//print(vec);
	findChildren(dynamic_cast<Node*>(root), vec);
	printTree(root, "");
	std::cout << " Children size " << root->getChildrenSize() << std::endl;
	return root;
}

void Engine::freeImageInitialize()
{
	FreeImage_Initialise();
}

void Engine::freeImageDeInitialize()
{
	FreeImage_DeInitialise();
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
//setta
void LIB_API Engine::setProjectionMatrix(glm::mat4 projection)
{
	currentCamera->setProjectionMatrix(projection);

}
void LIB_API Engine::enableZbuffer()
{
	glEnable(GL_DEPTH_TEST);
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

void LIB_API Engine::rotate()
{
	angleX++;
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

void Engine::switchLights()
{
	lighting = !lighting;
	enableLighting(lighting);
}
//TODO rimuovere una volta che c'è Scene Graph
void Engine::createTexture()
{
	Texture* t = new Texture("texture.bmp");
	//la matrice non la usa
	t->render(glm::mat4());
}

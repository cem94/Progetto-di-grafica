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

float angle = 5.f;

float fingerAngles[5];
// per il pollice
float angleX;
std::string fingerNames[5] = {"pollice", "indice", "medio", "anulare", "mignolo"};

// Gauntlet translate
bool translateUp = false;
int translateCnt = 0;

//lists
List* toRender = new List();
List *reflectedList = new List();

Engine* Engine::instance = nullptr;
//complete set of lists
std::vector<List*> Engine::lists = {};
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

    //aablita glew (un gestore di estensioni che usiamo per includere i metodi per vao usati per renderizzare le mesh)
    glewExperimental = GL_TRUE;  // Optional, but recommended
	//normalizza i vettori per il modello di illuminazione
    glEnable(GL_NORMALIZE);

    // Init di glew
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

	// attiva la luce sopra il guanto
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
//TODO:: credo che non lo useremo
void LIB_API Engine::mousePressed(int button, int state, int x, int y)
{
    if (state == GLUT_UP)
    {
        // isMousePressed = false;
    }
    if (state == GLUT_DOWN)
    {
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
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int LIB_API Engine::getWindowSizeX()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int LIB_API Engine::getWindowSizeY()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::mouseMoved(void (*mouseMoved)(int, int))
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
//TODO::  renderlo privato! -> non è neanche un metodo della classe per ora
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
	enableLighting(false);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE);
	//TODO:: wrappare
	glDisable(GL_TEXTURE_2D);
    char text[64];
    //colore testo
    
	strcpy(text, "[1] [2] [3] [4] turn on/off lights");
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 40.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
    
	sprintf(text, "FPS: %.1f", fps);
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 60.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

    strcpy(text, "[c] change camera");
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 80.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
    
	sprintf(text, "[r] rotate model");
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 100.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);
	//glEnable(GL_TEXTURE);
	glEnable(GL_TEXTURE_2D);
	enableLighting(true);
	//glEnable(GL_BLEND);
	//lighting = true;
}

/**
 * Starting from current node it recursively populate the scene graph
 * @param  currentNode the current node
 * @param2 nodes the list of remaining nodes to insert
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
    for (Node* n : palmo->getChildren())
    {
        if (n->getType() == Object::Type::CAMERA)
        {
            n = currentCamera;
            return;
        }
    }
    palmo->insert(currentCamera);
}

//TODO questo potrebbe anche stare in node
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
* read the scene graph and create various lists for lights, meshes and nodes
* @param  element root node
*/
//void  LIB_API Engine::createLists(Node* root)
//{
//    std::vector<Node*> children = root->getChildren();
//    toRender->add(root);
//	std::vector<Node*> allNodes;
//	getTreeAsList(root, allNodes);
//	if (root->getType() == Node::Type::MESH)
//    {
//        Mesh * mesh = (Mesh *)root;
//        if (mesh->getMaterial() != nullptr && mesh->getMaterial()->isTrasparent())
//        {
//            printf("Aggiungo mesh trasparente %s \n", mesh->getName().c_str());
//            transparentMeshes->add(element);
//        }
//    }
//    if (element->getType() == Node::Type::LIGHT)
//    {
//        //lista luci
//
//    }
//    for (Node * n : children)
//        createLists(n);
//}

/**
  * Set render and trasparent lists
  * @param  root scene graph
  */
void  LIB_API Engine::setLists(Node * root)
{
	toRender->add(root);
	for (Node * n : root->getChildren()) {
		if (n->getName() == "plane") {
			setAlphaToMaterial(root, 0.95f, "plane");
		}
		setLists(n);
	}
	/*
	//CEM se commento questo lo gira se no no non capisco perché -> mi una copia di root per fare le trasparenze
	Node* node = new Node{*root};
	printTree(node,"");
	setAlphaToMaterial(node, 0.9f, "plane");
	//riempie e ordina lista
	reflectedList->sort(node);
	lists.push_back(reflectedList);
	printf("We have %d elements to render\n", reflectedList->size());
	glm::mat4 reflection = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0));
	sortTrasparentMeshesList(reflectedList->getList());
	Node *r = reflectedList->at(0);
	r->setMatrix(r->getMatrix()*reflection);
	//std::vector<Node*> nodes;
	//reflectedList->getTreeAsList(node,nodes);
	//printf("size %d\n",nodes.size());
	*/
}

Camera * Engine::getCurrentCamera()
{
	return currentCamera;
}

void LIB_API Engine::render()
{
	glm::mat4 mat = glm::scale(glm::mat4(1), glm::vec3(1.0f, -1.0f, 1.0f));
	toRender->setIsRefletcion(true);
	glFrontFace(GL_CW);
	toRender->render(mat);
	glFrontFace(GL_CCW);
    toRender->setIsRefletcion(false);
	toRender->render(mat);
}

std::vector<List*> Engine::getLists()
{
	return lists;
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

void LIB_API Engine::moveCameraRight(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[0];
    currentCamera->setMatrix(glm::translate(matrix, mov));

    /*	old version
    	glm::vec3 mov = direction * currentCamera->getMatrix()[0];
    	glm::vec3 eye = currentCamera->getEye() + mov;
    	glm::vec3 center = currentCamera->getCenter() + mov;
    	currentCamera->setVec(eye, center, currentCamera->getUp());
    */
}

void LIB_API Engine::moveCameraUp(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[1];
    currentCamera->setMatrix(glm::translate(matrix, mov));

    /*  old verion
    	glm::vec3 mov = direction * currentCamera->getMatrix()[1];
    	glm::vec3 eye = currentCamera->getEye() + mov;
    	glm::vec3 center = currentCamera->getCenter() + mov;
    	currentCamera->setVec(eye, center, currentCamera->getUp());
    */
}

void LIB_API Engine::moveCameraForward(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[2];
    currentCamera->setMatrix(glm::translate(matrix, mov));

    /*	old version
    	glm::vec3 mov = direction * currentCamera->getMatrix()[2];
    	glm::vec3 eye = currentCamera->getEye() + mov;
    	glm::vec3 center = currentCamera->getCenter() + mov;
    	currentCamera->setVec(eye, center, currentCamera->getUp());
    */

}


void LIB_API Engine::rotateCameraRight(float angle)
{
    if (isMovableCamera())
        return;
    std::cout << "angle: " << angle << std::endl;
    glm::mat4 mat = currentCamera->getMatrix();
    glm::vec3 vec = mat[1];
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec);
    currentCamera->setMatrix(rotation * mat);
}

void LIB_API Engine::rotateCameraUp(float angle)
{
    if (isMovableCamera())
        return;
    std::cout << "angle: " << angle << std::endl;
    glm::mat4 mat = currentCamera->getMatrix();
    glm::vec3 vec = mat[0];
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle),vec);
    currentCamera->setMatrix(rotation * mat);
}

/**
* Change the current camera
*/
void LIB_API Engine::changeCamera(Node * root)
{
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
void LIB_API Engine::rotateModel(Node * root, float angle)
{
    Node* guardia = getNodeByName(root, "guardia");
    if (guardia != nullptr)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        guardia->setMatrix(guardia->getMatrix()*rotation);
    }
}

void LIB_API Engine::openThumb(Node *root) {

	//ottengo falangi
	std::string name = fingerNames[0];
	name.append("2");
	Node* phalanx2 = getNodeByName(root, name);
	Node* phalanx1 = phalanx2->getParent();
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(fingerAngles[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(fingerAngles[0]), glm::vec3(0.0f, 0.0f, 1.0f));

	phalanx1->setMatrix(phalanx1->getMatrix()*rotationY);
	phalanx2->setMatrix(phalanx2->getMatrix()*rotationY*rotationZ);
	fingerAngles[0] = 0;//l'angolo in y
}

/**
 * Close the thumb
 * @param  name1
 * @param2 name2
 * @return what it returns
 */

void LIB_API Engine::closeThumb(Node *root)
{

	if (fingerAngles[0] > 70.f) {
		return;
	}	
	fingerAngles[0] += angle;

	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, -1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));

	std::string name = fingerNames[0];
	name.append("2");
	Node* phalanx2 = getNodeByName(root, name);
	Node* phalanx1 = phalanx2->getParent();

	phalanx1->setMatrix(phalanx1->getMatrix()*rotationY);
	phalanx2->setMatrix(phalanx2->getMatrix()*rotationY*rotationZ);
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
        translateCnt++;
        if (translateUp)
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
        else
            translate =	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

        guardia->setMatrix(guardia->getMatrix() * translate * rotation);

        if (translateCnt > 180)
        {
            translateCnt = 0;
            translateUp = !translateUp;
        }
    }
}

/**
 * Close a finger of the hand
 * @param  scene scene graph
 * @param i number of the finger to close (starting from 0)
 * @param angle rotation angle
 */
void LIB_API Engine::closeFinger(Node * root, int i)
{
	if (fingerAngles[i] > 75.f)
	{
		return;
	}
	std::string name = fingerNames[i];
	name.append("3");
	Node* phalanx3 = getNodeByName(root, name);
	Node* phalanx2 = phalanx3->getParent();//padre di 3
	Node* phalanx1 = phalanx2->getParent();//padre di 2
	fingerAngles[i] += angle;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
    phalanx1->setMatrix(phalanx1->getMatrix()*rotationZ);
    phalanx2->setMatrix(phalanx2->getMatrix()*rotationZ);
    phalanx3->setMatrix(phalanx3->getMatrix()*rotationZ);
}

void LIB_API Engine::openFinger(Node * root, int i)
{
	std::string name = fingerNames[i];
	name.append("3");
	Node* phalanx3 = getNodeByName(root, name);
	Node* phalanx2 = phalanx3->getParent();//padre di 3
	Node* phalanx1 = phalanx2->getParent();//padre di 2
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(fingerAngles[i]), glm::vec3(0.0f, 0.0f, 1.0f));
	fingerAngles[i] = 0;
	phalanx1->setMatrix(phalanx1->getMatrix()*rotationZ);
	phalanx2->setMatrix(phalanx2->getMatrix()*rotationZ);
	phalanx3->setMatrix(phalanx3->getMatrix()*rotationZ);
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::closeHand(Node * root)
{
    closeThumb(root);
    closeFinger(root, 1);
    closeFinger(root, 2);
    closeFinger(root, 3);
    closeFinger(root, 4);
}
void LIB_API Engine::openHand(Node * root)
{
	openThumb(root);
	openFinger(root, 1);
	openFinger(root, 2);
	openFinger(root, 3);
	openFinger(root, 4);
}
void LIB_API Engine::free()
{
    //TODO::aggiungere altre cose da deinizializzare
	freeImageDeInitialize();
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


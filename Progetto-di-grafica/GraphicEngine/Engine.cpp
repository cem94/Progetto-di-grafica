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
//finger sensitivity
float angle = 5.f;
float fingerAngles[5];
std::string fingerNames[5] = { "pollice", "indice", "medio", "anulare", "mignolo" };

// Gauntlet translate
bool translateUp = false;
int translateCnt = 0;

List* toRender = new List();
Engine* Engine::instance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printList(std::vector<Node*> list)
{
    for (auto n : list)
    {
        std::cout << n->getName().c_str() << std::endl;
        std::cout << n->getId() << std::endl;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
 * @param  mouveMoved passive motion function callback
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
 * Setter for timer callback here we calculate fps
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
 * Changes lighting state
 */
void LIB_API Engine::switchLights()
{
    lighting = !lighting;
    enableLighting(lighting);
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
    //TODO:: wrappare
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
    glEnable(GL_TEXTURE_2D);
    enableLighting(true);
}

/**
 * Starting from current node it recursively populate the scene graph
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
    printTree(root, "");
    return root;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  * Set render and trasparent lists
  * @param  root scene graph
  */
void  LIB_API Engine::createRenderList(Node * root)
{
    setAlphaToMaterial(root, 0.5f, "plane");
    toRender = new List(root);
    toRender->sort();
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
Camera * Engine::getCurrentCamera()
{
    return currentCamera;
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::render()
{
    toRender->isReflection(true);
    glm::mat4 mat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f));
    //clockwise
    glFrontFace(GL_CW);
    toRender->render(mat);
    //counter clockwise
    glFrontFace(GL_CCW);
    toRender->isReflection(false);
    toRender->render(mat);
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

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::moveCameraRight(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[0];
    currentCamera->setMatrix(glm::translate(matrix, mov));
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::moveCameraUp(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[1];
    currentCamera->setMatrix(glm::translate(matrix, mov));
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::moveCameraForward(float direction)
{
    if (!isMovableCamera())
        return;
    glm::mat4 matrix = currentCamera->getMatrix();
    glm::vec3 mov = direction * 5.0f * matrix[2];
    currentCamera->setMatrix(glm::translate(matrix, mov));
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
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
/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::rotateCameraUp(float angle)
{
    if (isMovableCamera())
        return;
    std::cout << "angle: " << angle << std::endl;
    glm::mat4 mat = currentCamera->getMatrix();
    glm::vec3 vec = mat[0];
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vec);
    currentCamera->setMatrix(rotation * mat);
}

/**
* Change the current camera
*/
void LIB_API Engine::changeCamera(Node * root)
{
    activeCamera = (activeCamera + 1) % cameras.size();
    currentCamera = cameras.at(activeCamera);
    loadMatrix(currentCamera->getMatrix());
}

/**
 * Rotate model
 * @param  root our scene graph
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
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::openThumb(Node *root)
{

    //ottengo falangi
    std::string name = fingerNames[0];
    name.append("2");
    Node* phalanx2 = getNodeByName(root, name);
    Node* phalanx1 = phalanx2->getParent();
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(fingerAngles[0]), glm::vec3(-1.0f, 1.0f, 1.0f));
    phalanx1->setMatrix(phalanx1->getMatrix()*rotationY);
    phalanx2->setMatrix(phalanx2->getMatrix()*rotationY);
    fingerAngles[0] = 0;
}

/**
 * Close the thumb
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void LIB_API Engine::closeThumb(Node *root)
{
    if (fingerAngles[0] > 65.f)
    {
        return;
    }
    fingerAngles[0] += angle;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, -1.0f, -1.0f));
    std::string name = fingerNames[0];
    name.append("2");
    Node* phalanx2 = getNodeByName(root, name);
    Node* phalanx1 = phalanx2->getParent();
    Node* gemma = phalanx1->getChildren().at(1);
    phalanx1->setMatrix(phalanx1->getMatrix()*rotation);
    phalanx2->setMatrix(phalanx2->getMatrix()*rotation);
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
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

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
    Node* phalanx2 = phalanx3->getParent();
    Node* phalanx1 = phalanx2->getParent();
    fingerAngles[i] += angle;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, -1.0f));
    phalanx1->setMatrix(phalanx1->getMatrix()*rotation);
    phalanx2->setMatrix(phalanx2->getMatrix()*rotation);
    phalanx3->setMatrix(phalanx3->getMatrix()*rotation);
}

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::openFinger(Node * root, int i)
{
    std::string name = fingerNames[i];
    name.append("3");
    Node* phalanx3 = getNodeByName(root, name);
    Node* phalanx2 = phalanx3->getParent();
    Node* phalanx1 = phalanx2->getParent();
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(fingerAngles[i]), glm::vec3(0.0f, 0.0f, 1.0f));
    fingerAngles[i] = 0;
    phalanx1->setMatrix(phalanx1->getMatrix()*rotation);
    phalanx2->setMatrix(phalanx2->getMatrix()*rotation);
    phalanx3->setMatrix(phalanx3->getMatrix()*rotation);
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

/**
 * Close hand
 * @param  root scene graph
 * @param angle rotation angle of fingers
 */
void LIB_API Engine::openHand(Node * root)
{
    openThumb(root);
    openFinger(root, 1);
    openFinger(root, 2);
    openFinger(root, 3);
    openFinger(root, 4);
}

//TODO::aggiungere altre cose da deinizializzare
void LIB_API Engine::free()
{
    freeImageDeInitialize();
}

void LIB_API Engine::setAlphaToMaterial(Node * root, float alpha, std::string nodeName)
{
    Node* node = getNodeByName(root, nodeName);
    if (node != nullptr)
    {
        Mesh* mesh = (Mesh*)node;
        mesh->getMaterial()->setAlpha(alpha);
        printf("Setted alpha of %s\n", mesh->getName().c_str());
    }
}

/**
* depth-sorting (back to front) method for transparent meshes
* @param two list element to compare
*/
//bool listNodeCompare(Node*a, Node *b)
//{
//	glm::mat4 first = currentCamera->getMatrix()* a->getMatrix();
//	glm::mat4 second = currentCamera->getMatrix()*b->getMatrix();
//	return (float)first[3].z > (float)second[3].z;
//}

//void LIB_API Engine::sortTrasparentMeshesList(std::vector<Node*>& transparentMeshes)
//{
//	glDepthMask(GL_FALSE);
//	std::sort(transparentMeshes.begin(), transparentMeshes.end(), listNodeCompare);
//	glDepthMask(GL_TRUE);
//}

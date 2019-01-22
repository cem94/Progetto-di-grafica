#include "Engine.h"
#include <GL/freeglut.h>

/**
 * List constructor
 */
List::List()
{
}
/**
 * List constructor it populates the list from a tree through the getTreeAsList method.
 */
List::List(Node * root)
{
    getTreeAsList(root, list);
}

/**
* List Destructor
*/
List::~List()
{
}

/**
 * Getter for list
 * @return list
 */
std::vector<Node*> List::getList() const
{
    return this->list;
}
/**
 * Setter for list
 * @param  list
 */
void List::setList(std::vector<Node*> list)
{
    this->list = list;
}

/**
 * Getter for reflection
 * @return reflection
 */
bool List::isReflection() const
{
    return this->reflection;
}
/**
 * Setter for reflection
 */
void List::isReflection(bool reflection)
{
    this->reflection = reflection;
}
/**
* Reserve memory for list
* @param  size how much we want to reserve
*/
void List::reserve(int size)
{
    this->list.reserve(size);
}

/**
 * Add a node to the list
 * @param  node the node we want to add
 */
void List::add(Node* node)
{
    this->list.push_back(node);
}

/**
 * Removes a node from the list given its position
 * @param  position index of the desired node
 */
void List::remove(int position)
{
    list.erase(list.begin() + position);
}

/**
 * Return the element at the position passed as an argument or nullptr if out of range
 * @param  position the position of the desired element
 * @return if the range is valid it returns the requested node, otherwise it return nullptr
 */
Node* List::at(int position)
{
    if (position < this->list.size() && position >= 0)
    {
        return list.at(position);
    }
    return nullptr;
}

/**
 * insert a list of elements at the end of our list
 * @param  list of elements to add
 */
void List::insert(std::vector<Node*> elements)
{
    list.insert(list.end(), elements.begin(), elements.end());
}

/**
 * Give the size of the list
 * @return size of the list
 */
int List::size()
{
    return (int)this->list.size();
}

/**
 * Get tree as list populates the vector of nodes passed as an argument with the content of the given scene graph
 *
 */
void List::getTreeAsList(Node *root, std::vector<Node*>& nodes)
{
    const int size = root->getChildrenSize();
    nodes.push_back(root);
    for (int i = 0; i < size; i++)
    {
        getTreeAsList(root->getChildren().at(i), nodes);
    }
}

/**
 * Create a series of lists containing nodes, lights and meshes then put them in the correct order in the list
 */
void List::sort()
{
    std::vector<Node*> nodes;
    std::vector<Light*> lights;
    std::vector<Mesh*> meshes;
    for (std::vector<Node*>::iterator n = list.begin(), end = list.end(); n != end; ++n)
    {
        if ((*n)->getType() == Object::NODE)
        {
            nodes.push_back((*n));
            continue;
        }
        if ((*n)->getType() == Object::LIGHT)
        {
            lights.push_back(dynamic_cast<Light*>((*n)));
            continue;
        }
        if ((*n)->getType() == Object::MESH)
        {
            meshes.push_back(dynamic_cast<Mesh*>((*n)));
            continue;
        }
    }
    list.clear();
    list.insert(list.end(), nodes.begin(), nodes.end());
    list.insert(list.end(), lights.begin(), lights.end());
    list.insert(list.end(), meshes.begin(), meshes.end());
}


/**
 * Render for list
 * @param  matrix render matrix (not used)
 */
void List::render(glm::mat4 scaling)
{
    Node * root = list.at(0);
    root->setMatrix(root->getMatrix() * scaling);
    const glm::mat4 cameraMat = Engine::getInstance().getCurrentCamera()->getMatrix();
    const bool reflection = isReflection();
    for (std::vector<Node*>::iterator n = list.begin(), end = list.end(); n != end; ++n)
    {
        glm::mat4 renderMatrix = cameraMat * (*n)->getFinalMatrix();
        if (reflection && (*n)->getName() == "plane")
        {
            continue;
        }
        (*n)->render(renderMatrix);
    }
}

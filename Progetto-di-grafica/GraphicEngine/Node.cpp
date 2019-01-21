#include "Engine.h"

static int counter;

/**
 * Node constructor
 */
Node::Node()
{
    this->setId(counter);
	counter++;

}

Node::Node(Node * parent)
{ 
	if (parent != nullptr) 
		this->parent = parent;
}


/**
 * Node destructor
 */
Node::~Node()
{ 
	//remove children
	for (Node* n : this->children) 
		delete (n);
	//clear vector
	this->children.clear();

	//remove it from parent
	int cnt = 0;
	for (Node* n : this->parent->getChildren()) 
	{
		//remove children
		if (n->getId() == this->getId()) {
			this->parent->remove(cnt);
			break;
		}
		cnt++;
	}
}

/**
 * Getter for node parent
 * @return node parent
 */
Node * Node::getParent() const
{
    return parent;
}

/**
 * Setter for node parent
 * @param  parent node parent
 */
void Node::setParent(Node * parent)
{
    this->parent = parent;
}

/**
 * Getter for node children
 * @return node children
 */
std::vector<Node*> Node::getChildren() const
{
    return children;
}

/**
 * Getter for node matrix
 * @return node matrix
 */
glm::mat4 Node::getMatrix()
{
    return matrix;
}

/**
 * Setter for node matrix
 * @param  matrix node matrix
 */
void Node::setMatrix(glm::mat4 matrix)
{
    this->matrix = matrix;
}

/**
 * Insert a node in the current node childrens and set the current node as the father
 */
void Node::insert(Node * node)
{
    node->setParent(this);
    children.push_back(node);
}

/**
 * Remove a node from current node childrens given its position
 * @param  position of the node to remove
 */
void Node::remove(int position)
{
    if (getChildrenSize() > position && position >= 0)
    {
        auto to_remove = children.at(position);
        children.erase(children.begin() + position);
        free(to_remove);
    }
}

/**
 * Remove a node from the current node childrens
 * @param  node the node to remove
 */
void Node::remove(Node * node)
{
    int i = 0;
    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
    {
        if ((*it) == node)
            break;
        i++;
    }
    remove(i);
}

/**
 * Getter for the children size
 * @return current node children size
 */
int Node::getChildrenSize() const
{
    return (int)this->children.size();
}

/**
 * Method that reserves memory for this node's childrens
 * @param  size children size
 */
void Node::setChildrenSize(unsigned int size)
{
    children.reserve(size);
}

/**
 * Getter for node final matrix
 * @return this node final matrix
 */
glm::mat4 Node::getFinalMatrix()
{
    if (!parent)
        return matrix;
    return parent->getFinalMatrix()*matrix;
}

/**
 * Getter for childrens capacity
 * @return this node's childrens capacity
 */
int Node::getCapacity() const
{
    return (int)this->children.capacity();
}

/**
 * Render for node (empty)
 * @param  renderMatrix node render matrix
 */
void Node::render(glm::mat4 renderMatrix)
{
}
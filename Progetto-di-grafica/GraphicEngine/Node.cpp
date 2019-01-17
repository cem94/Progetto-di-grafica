#include "Engine.h"

static int counter;
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node::Node()
{
	//TODO Cem magari spostare il contatore nell'ovoreader e settare l'id da lì
	this->setId(counter++);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node::~Node()
{
}

// Getters & Setters //
Node * Node::getParent() const
{
	return parent;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Node::setParent(Node * parent)
{
	this->parent = parent;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
std::vector<Node*> Node::getChildren() const
{
	return children;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::mat4 Node::getMatrix()
{
	return matrix;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Node::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
 //Inserisce il nodo fra i  figli del nodo corrente
void Node::insert(Node * node)
{
	node->setParent(this);
	children.push_back(node);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
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
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
 //rimuove node
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

//ritorna il numero di figli del nodo corrente
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int Node::getChildrenSize() const
{
	return (int)this->children.size();
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Node::setChildrenSize(unsigned int size)
{
	children.reserve(size);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
glm::mat4 Node::getFinalMatrix()
{
	if (!parent)
		return matrix;
	return parent->getFinalMatrix()*matrix;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
int Node::getCapacity() const
{
	return (int)this->children.capacity();
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Node::render(glm::mat4 renderMatrix)
{
}
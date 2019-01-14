#include "Engine.h"

static int counter;

Node::Node()
{
	this->setId(counter++);
}

Node::~Node()
{
}
// Getters & Setters //
Node * Node::getParent() const
{
	return parent;
}

void Node::setParent(Node * parent)
{
	this->parent = parent;
}

std::vector<Node*> Node::getChildren() const
{
	return children;
}

void Node::setChildren(std::vector<Node*> children)
{
	this->children = children;
}

glm::mat4 Node::getMatrix() const
{
	return this->matrix;
}

void Node::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}
//Inserisce il nodo fra i  figli del nodo corrente
void Node::insert(Node * node)
{
	node->setParent(this);
	children.push_back(node);
}
/* TODO se possibile Use shrink_to_fit() to release memory consumed by the vector – clear() or erase() does not release memory.*/
void Node::remove(int position)
{
	if (children.size() > 0 && position > 0 && position < children.size())
	{
		children.erase(children.begin() + position);
	}
}
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
Node * Node::operator[](int position)
{
	if (position >= 0 && position < childrenSize)
	{
		return children.at(position);
	}
	return nullptr;
}
//ritorna il numero di figli del nodo corrente
int Node::getChildrenSize() const
{
	return this->childrenSize;
}
//TODO da rivedere -> i metodi insert remove modificano la dimensione, noi ritorniamo sempre quella originale
void Node::setChildrenSize(unsigned int size)
{
	this->childrenSize = size;
	children.reserve(size);
}
//TODO sostituirlo dove necessario
glm::mat4 Node::getFinalMatrix()
{
		if (!parent)
			return matrix;
		return parent->getFinalMatrix()*matrix;
	
}

void Node::render(glm::mat4 renderMatrix)
{
	//empty
}

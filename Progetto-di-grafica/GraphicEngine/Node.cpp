#include "Engine.h"

Node::Node()
{
}


Node::~Node()
{
}

Node * Node::getParent() const
{
    return parent;
}

void Node::setParent(Node * parent)
{
	this->parent = parent;
}

Node * Node::getChildren() const
{
    return children;
}

void Node::setChildren(Node * children)
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

//ritorna il numero di figli
int Node::getChildrenSize() const
{
	//return this->children.size();
	return 0;
}

void Node::render(glm::mat4 rendermatrix)
{
//TODO
}

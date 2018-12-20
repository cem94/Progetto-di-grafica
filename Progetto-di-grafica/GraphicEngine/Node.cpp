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

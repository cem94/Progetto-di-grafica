#include "Engine.h"

Node::Node()
{
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
	//setto padre
	node->setParent(this);
	//lo metto in fondo alla lista
	children.push_back(node);
}
/* TODO se possibile Use shrink_to_fit() to release memory consumed by the vector – clear() or erase() does not release memory.*/
void Node::remove(int position)
{
	//TODO semplificare if
	if (children.size() > 0 && position > 0 && position < children.size())
	{
		children.erase(children.begin() + position);
	}
}
//rimuove node
void Node::remove(Node * node)
{
	int index = 0;
	//iteratore per calcolare l'indice del nodo da rimuovere
	for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it) == node)
			break;
		index++;
	}
	remove(index);
	/*if (index < children.size())
		children.erase(children.begin() + index);*/
}

//ritorna il numero di figli
int Node::getChildrenSize() const
{
	return (int) this->children.size();
}

Object::Type Node::getType() const
{
	return NODE;
}

void Node::render(glm::mat4 rendermatrix)
{
	//empty
}

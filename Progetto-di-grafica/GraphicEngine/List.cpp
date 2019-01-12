#include "Engine.h"

List::List()
{
}

List::~List()
{
}

std::list<Node*> List::getList() const
{
	return this->objects;
}

void List::setList(std::list<Node*> objects)
{
	this->objects = objects;

}

//aggiunge oggetto a lista istanze e salva matrice(in worlCoordinates)
void List::add(Node* node, glm::mat4 matrix) 
{
	node->setMatrix(matrix);
	this->objects.push_back(node);
}

void List::remove(int position)
{
	std::list<Node*>::iterator iterator;
	advance(iterator, position);
	this->objects.erase(iterator);
}

Node* List::at(int position)
{
	if (position < this->objects.size())
	{
		std::list<Node*>::iterator iterator;
		advance(iterator, position);
		return *iterator;
	}
	return nullptr;
}

void List::render(glm::mat4 renderMatrix)
{
	//Empty
}
//non ritorna nulla -> tipo lista non c'è
Object::Type List::getType() const
{
	return Object::Type();
}

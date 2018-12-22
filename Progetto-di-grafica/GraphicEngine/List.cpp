#include "Engine.h"

List::List()
{
}

List::~List()
{
}

std::vector<Object*> List::getList() const
{
	return this->objects;
}

void List::setList(std::vector<Object*> objects)
{
	this->objects = objects;

}

void List::render(glm::mat4 renderMatrix)
{
}

//aggiunge oggetto TODO capire come settare worlCoordinates
void List::addObject(Object* obj)
{
	//Element *element = new Element(node, worldCoordinate);
	this->objects.push_back(obj);
}

void List::remove(Object * node)
{
	//TODO
}

void List::remove(int position)
{
	//TODO
}

Object * List::at(int position)
{
	//TODO
	return nullptr;
}
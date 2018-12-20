#include "Engine.h"

List::List()
{
}


List::~List()
{
}
//Getter
std::vector<Object*> List::getList() const
{
    return this->objects;
}
//Setter
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

void List::removeObject(Object * node)
{
//TODO
}





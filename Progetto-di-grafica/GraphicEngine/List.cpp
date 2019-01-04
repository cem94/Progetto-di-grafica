#include "Engine.h"

List::List()
{
}

List::~List()
{
}

std::vector<List::Element*> List::getList() const
{
	return this->objects;
}

void List::setList(std::vector<Element*> objects)
{
	this->objects = objects;

}


//aggiunge oggetto a lista istanze e salva matrice(in worlCoordinates)
void List::add(Object* obj, glm::mat4 matrix)
{
	Element *element = new Element(obj, matrix);
	this->objects.push_back(element);
}

void List::remove(int position)
{
	std::vector<Element*>::iterator iterator;
	advance(iterator, position);
	this->objects.erase(iterator);
}

List::Element * List::at(int position)
{
	if (position < this->objects.size())
	{
		std::vector<Element*>::iterator iterator;
		advance(iterator, position);
		return *iterator;
	}
	return nullptr;
}

void List::render(glm::mat4 renderMatrix)
{
	//Empty
}
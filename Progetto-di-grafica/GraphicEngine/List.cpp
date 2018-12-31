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
	//Empty
}
//TODO provare ad usare NODE
//aggiunge oggetto a lista istanze e salva matrice(in worlCoordinates)
void List::addObject(Object* obj, glm::mat4 matrix)
{
	this->objects.push_back(obj);
	this->matrices.push_back(matrix);
}

void List::remove(int position)
{
	//creo iterator
	std::vector<Object*>::iterator iterator;
	//avanzo fino a pos desiderata
	advance(iterator, position);
	//cancello
	this->objects.erase(iterator);
}

Object * List::at(int position)
{
	//TODO migliorare
	if (position < this->objects.size())
	{
		//std::vector<Object*>::iterator iterator = this->objects.begin();
		std::vector<Object*>::iterator iterator;
		advance(iterator, position);
		return *iterator;
	}
	return nullptr;
}
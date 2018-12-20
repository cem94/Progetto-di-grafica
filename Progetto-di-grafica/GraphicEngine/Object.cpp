#include "Engine.h"

Object::~Object()
{
}

int Object::getID() const
{
	return 0;
}

int Object::generateID()
{
    //this->id = time(nullptr) + rand();
    return 0;
}

std::string Object::getName() const
{
	return nullptr;
}

void Object::setName(std::string name)
{
	//this->name = name;
}

Object* Object::findByName(std::string name)
{
    return nullptr;
}

Object* Object::findByID(int id)
{
    return nullptr;
}

#include "Object.h"
#include <ctime>


Object::~Object()
{
}

int Object::generateID()
{
	this->id = time(nullptr) + rand();
	return 0;
}

Object* Object::findByName(std::string name)
{
	return nullptr;
}

Object* Object::findByID(int id)
{
	return nullptr;
}

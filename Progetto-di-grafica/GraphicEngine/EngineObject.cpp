#include "EngineObject.h"
#include <ctime>


EngineObject::~EngineObject()
{
}

int EngineObject::generateID()
{
	this->id = time(nullptr) + rand();
	return 0;
}

EngineObject* EngineObject::findByName(string name)
{
	return nullptr;
}

EngineObject* EngineObject::findByID(int id)
{
	return nullptr;
}

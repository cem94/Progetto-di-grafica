#include "Engine.h"

int Object::getId() const
{
		return this->id;
}

void Object::setId(int id)
{
		this->id = id;	
}

std::string Object::getName() const
{
		return this->name;
}

void Object::setName(std::string name)
{
		this->name = name;	
}

void Object::setType(Type type)
{
		this->type = type;	
}

Object::Type Object::getType() const
{
		return type;
}

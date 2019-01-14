#pragma once
/* Base class used by all the derived classes.This class is responsible for
 * keeping track of the existing objects, forcing some required API (virtual)
 * methods and providing a unique ID to each object. */
#include <chrono>

class  Object {
public:
	enum Type { CAMERA, LIGHT, MATERIAL, MESH, NODE, TEXTURE, NONE };
	int getID() const { return this->id; };
	void setID(int id)  { this->id=id; };
	int generateID() {
		return counter++; 
	};
	std::string getName() const { return this->name; };
	void setName(std::string name) { this->name = name; };
	virtual void render(glm::mat4 rendermatrix) = 0;
	virtual Type getType() const = 0;
	void setType(Type type) { this->type = type; }
private:
	int id;
	std::string name;
	Type type;
	static int counter;
};
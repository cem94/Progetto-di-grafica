#pragma once
/* Base class used by all the derived classes.This class is responsible for
 * keeping track of the existing objects, forcing some required API (virtual)
 * methods and providing a unique ID to each object. */

class  Object {
public:
	enum Type { OBJECT = 0, CAMERA, LIGHT, MATERIAL, MESH, NODE, TEXTURE };
	int getId() const { return this->id; };
	void setId(int id)  { this->id=id; };
	std::string getName() const { return this->name; };
	void setName(std::string name) { this->name = name; };
	void setType(Type type) { this->type = type; }
	virtual void render(glm::mat4 rendermatrix) = 0;
	 Type getType() const { return type; };
private:
	Type type;
	int id;
	std::string name;
};
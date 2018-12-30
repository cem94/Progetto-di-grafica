#pragma once
/* Base class used by all the derived classes.This class is responsible for keeping track of the existing objects, forcing some required API (virtual) methods and providing a unique ID to each object.
*  Tutto inline perché è una classe astratta-> no cpp */
class Object
{
public:
	Object() {};
	virtual ~Object() {};
	enum Type {
		CAMERA,
		LIGHT,
		MATERIAL,
		MESH,
		NODE,
		TEXTURE
	};
	int getID() const { return this->id; };
	int generateID() {/*TODO*/ };
	std::string getName() const { return this->name; };
	void setName(std::string name) { this->name = name; };
	Object* findByName(std::string name) {/*TODO*/ };
	Object* findByID(int id) { /*TODO*/ };
	//metodo che renderizza l'oggetto -> le sottoclassi dovranno implementarlo
	virtual void render(glm::mat4 rendermatrix) = 0;
	virtual Type getType() const = 0;
private:
	int id;
	std::string name;
};
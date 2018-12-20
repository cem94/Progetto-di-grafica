#pragma once
//Tutto inline perché è una classe astratta-> no cpp
class Object
{
public:
    Object() {};
	virtual ~Object() {};
	int getID() const { return this->id; };
	int generateID() {
	//TODO
	};
	std::string getName() const { return this->name; };
	void setName(std::string name) { this->name = name; };
	Object* findByName(std::string name) {
		//TODO
	};
	Object* findByID(int id) {
		//TODO
	};
	//metodo che renderizza l'oggetto -> le sottoclassi dovranno implementarlo
	virtual void render(glm::mat4 rendermatrix) = 0;
private:
    int id;
    std::string name;
};
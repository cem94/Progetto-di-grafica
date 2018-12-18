#pragma once
#include <vector>
#include <string>
using namespace std;

class Object
{
public:
	Object() {};
	virtual ~Object();
	int getID();
	int generateID();
	std::string getName();
	void setName(std::string name);
	Object* findByName(std::string name);
	Object* findByID(int id);
	//TODO: Mandatory

private:
	std::vector<Object> listObject;
	int id;
	std::string name;
};


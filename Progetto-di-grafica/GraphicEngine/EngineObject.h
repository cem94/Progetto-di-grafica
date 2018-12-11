#pragma once
#include <vector>
using namespace std;

class EngineObject
{
public:
	EngineObject() {};
	virtual ~EngineObject();
	int getID();
	int generateID();
	string getName();
	void setName(string name);
	EngineObject* findByName(string name);
	EngineObject* findByID(int id);
	//TODO: Mandatory

private:
	vector<EngineObject> listObject;
	int id;
	string name;
};


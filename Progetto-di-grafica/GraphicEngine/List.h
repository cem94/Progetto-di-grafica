#pragma once
#include "EngineObject.h"

class List : public EngineObject
{
public:
	List();
	virtual ~List();

	vector<EngineObject> getList();
	void addObject(EngineObject obj);
	void removeObject(EngineObject obj);
	void renderList();

private:
	vector<EngineObject> list;
};


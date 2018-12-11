#pragma once
#include <glm.hpp>
#include "EngineObject.h"

class EngineNode : public EngineObject
{
public:
	EngineNode();
	virtual ~EngineNode();

	EngineNode* getParent();
	void setParent(EngineNode* parent);
	EngineNode* getChildren();
	void setChildren(EngineNode* children);

	//TODO: controllare se vec4 o vec3
	virtual glm::vec4 getPosition() = 0;

private:
	EngineNode* parent;
	EngineNode* children;
};


#pragma once
   #include <glm/glm.hpp>
   #include "Object.h"

class Node : public Object
{
public:
	Node();
	virtual ~Node();

	Node* getParent();
	void setParent(Node* parent);
	Node* getChildren();
	void setChildren(Node* children);

	//TODO: controllare se vec4 o vec3
	virtual glm::vec4 getPosition() = 0;

private:
	Node* parent;
	Node* children;
};


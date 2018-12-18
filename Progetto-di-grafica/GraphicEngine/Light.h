#pragma once
#include "Node.h"

class Light : public Node
{
public:
	Light();
	virtual ~Light();

	short getIntensity();
	void setIntensity(short intensity);
	void renderLight();
	//TODO: capire come fare
	void typeLight();

	// Ereditato tramite EngineNode
	virtual glm::vec4 getPosition() override;

private:
	short intensity;
	glm::vec4 position;
};


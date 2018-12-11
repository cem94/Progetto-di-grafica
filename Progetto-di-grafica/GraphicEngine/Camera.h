#pragma once
#include "EngineNode.h"

class Camera : public EngineNode
{
public:
	Camera();
	virtual ~Camera();

	void createCamera();
	void moveCamera(glm::mat4 matrix);
	void zoomCamera(const int zoom);
	void inverseCamera();
	//TODO: capire come si fa
	void typeCamera();

	// Ereditato tramite EngineNode
	virtual glm::vec4 getPosition() override;

private: 
	glm::vec4 position;
};


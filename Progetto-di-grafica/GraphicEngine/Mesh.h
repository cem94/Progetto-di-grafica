#pragma once
#include "EngineNode.h"

class Mesh : EngineNode
{
public:
	Mesh();
	virtual ~Mesh();
	
	vector<glm::vec4> getVertexes();
	void renderMesh();
	//TODO: getUsedMaterials

	// Ereditato tramite EngineNode
	virtual glm::vec4 getPosition() override;

private:
	vector<glm::vec4> vertexes;
};


#pragma once

class  Camera : public Node
{
public:
	Camera();

	virtual ~Camera();
	void createCamera();
	void moveCamera(glm::mat4 matrix);
	void zoomCamera(const int zoom);
	glm::mat4 inverseCamera() const;
	//TODO: capire come si fa
	void typeCamera();
	void setProjectionMatrix(glm::mat4 projection);
	// Ereditato tramite Node
	virtual glm::vec4 getPosition() const override;

private:
	glm::vec4 position;
	glm::mat4 projectionMatrix;
};


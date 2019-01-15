#pragma once
/*This class represents a camera. Settings should comprise both orthographic and perspective projections, and the necessary math to retrieve the camera inverse matrix.*/

class Camera : public Node
{
public:
	Camera();
	virtual ~Camera();
	void setProjectionMatrix(glm::mat4 projection);
	//TODO:: GREG sono da rimuovere, non le usiamo ed esistono nella classe NODE
	//void setMatrix(glm::mat4 matrix);
	//glm::mat4 inverseCamera() const;
	//Ereditato da object
	void render(glm::mat4 renderMatrix);
	//Type getType() const override;
private:
	glm::mat4 projectionMatrix;
};
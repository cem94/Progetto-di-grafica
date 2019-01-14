#pragma once
/*This class represents a camera. Settings should comprise both orthographic and perspective projections, and the necessary math to retrieve the camera inverse matrix.*/
class Camera : public Node
{
public:
	Camera();
	virtual ~Camera();
	void setProjectionMatrix(glm::mat4 projection);
	void setMatrix(glm::mat4 matrix);
	glm::mat4 inverseCamera() const;
	//Ereditato da object
	 void render(glm::mat4 renderMatrix) override;
	 Type getType() const override;
private:
	//contiene la matrice di proiezione -> glm::lookAt(eye,center,up)
	glm::mat4 projectionMatrix;
};


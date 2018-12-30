#pragma once
/*This class represents a camera. Settings should comprise both orthographic and perspective projections, and the necessary math to retrieve the camera inverse matrix.*/
class  Camera : public Node
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
	//TODO//
	void createCamera();
	void moveCamera(glm::mat4 matrix);
	void zoomCamera(const int zoom);
private:
	//	glm::vec4 position; da rimuovere la matrice(quella in Node) contiene la posizione -> settata tramite lookAt(eye,center,up)
	glm::mat4 projectionMatrix;
};


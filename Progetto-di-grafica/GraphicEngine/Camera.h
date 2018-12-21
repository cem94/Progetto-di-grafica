#pragma once
/*This class represents a camera. Settings should comprise both orthographic and perspective projections, and the necessary math to retrieve the camera inverse matrix.*/
class  Camera : public Node
{
public:
	Camera();

	virtual ~Camera();
	void createCamera();
	void moveCamera(glm::mat4 matrix);
	void zoomCamera(const int zoom);
	glm::mat4 inverseCamera() const;
	//TODO: creare enum dei tipi
	void typeCamera();
	void setProjectionMatrix(glm::mat4 projection);
	void setMatrix(glm::mat4 matrix);
	void render(glm::mat4 renderMatrix) override;

private:
//	glm::vec4 position; da rimuovere la matrice(quella in Node) contiene la posizione -> settata tramite lookAt(eye,center,up)
	glm::mat4 projectionMatrix;
};


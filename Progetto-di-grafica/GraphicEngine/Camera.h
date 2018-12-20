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
	//TODO: creare enum dei tipi
	void typeCamera();
	void setProjectionMatrix(glm::mat4 projection);

private:
//	glm::vec4 position; da rimuovere la matrice(quella in Node) contiene la posizione -> settata tramite lookAt(eye,center,up)
	glm::mat4 projectionMatrix;
};


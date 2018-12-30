#pragma once
/*Light class that implements the main types of light introduced in the course. This class includes the necessary methods for applying its settings to OpenGL.      */
class Light : public Node
{
public:
	Light();
	virtual ~Light();
	//Getters & Setters
	short getIntensity() const;
	void setIntensity(short intensity);
	void setAmbient(glm::vec4 ambient);
	void setDiffuse(glm::vec4 diffuse);
	void setSpecular(glm::vec4 specular);
	//Ereditato da object
	void render(glm::mat4 renderMatrix) override;
	Type getType() const override;
private:
	//impostazioni luce//
	glm::vec4 position;
	glm::vec4 color;
	short intensity;
	//tipi di luce
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};


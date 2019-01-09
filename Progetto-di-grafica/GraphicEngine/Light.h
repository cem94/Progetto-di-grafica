#pragma once
/*Light class that implements the main types of light introduced in the course. This class includes the necessary methods for applying its settings to OpenGL.      */
class Light : public Node
{
public:
	Light();
	Light(const char* name) : Node(name){}
	virtual ~Light();
	//Getters & Setters
	short getIntensity() const;
	void setIntensity(short intensity);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	//Ereditato da object
	void render(glm::mat4 renderMatrix) override;
	Type getType() const override;
	//TODO
	enum SubType { DIRECTIONAL, OMNI, SPOTLIGHT};
	SubType getSubType() const;
	void setSubType(SubType subtype);
	//TODO finire switch GLenum
	int getLightNumber();
	void enableLight(bool enable);
	void setColor(glm::vec3 color);
	void setPosition(glm::vec4 position);
	//direzione luce spotlight
	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
	//l'angolo(di cutoff) massimo di diffusione di una fonte di luce (180 = uniform light distribution)
	void setAngle(float angle);
	float getAngle() const;
	//raggio della fonte di luce (sfera)
	float getRadius() const;
	void setRadius(float radius);
	float getCutoff() const;
	void setCutoff(float cutoff);
	void setMatrix(glm::mat4 matrix);
private:
	//impostazioni luce//
	glm::vec4 position;
	short intensity;
	//tipi di luce
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	//direzione della luce
	glm::vec3 direction;
	//colore della luce RGB
	glm::vec3 color;
	//sottotipo luce(directional, omni, spotlight)
	SubType subType;
	float cutoff;
	float radius;
	float angle;
};
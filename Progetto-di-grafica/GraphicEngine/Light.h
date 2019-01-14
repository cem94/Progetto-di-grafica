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
	
	//We dont 'use DIRECTIONAL, remove it.
	enum SubType {OMNI, SPOTLIGHT, DIRECTIONAL};
	SubType getSubType() const;
	void setSubType(SubType subtype);
	Type getType() const override;

	int getLightNumber();
	void enableLight(bool enable);
	void setColor(glm::vec4 color);
	//posizione della luce, per tutte e 3
	void setPosition(glm::vec4 position);
	//direzione luce spotlight
	glm::vec3 getDirection();
	void setDirection(glm::vec4 direction);
	//l'angolo(di cutoff) massimo di diffusione di una fonte di luce (180 = uniform light distribution)
	void setAngle(float angle);
	float getAngle() const;
	//raggio della fonte di luce (sfera)
	float getRadius() const;
	void setRadius(float radius);
	float getCutoff() const;
	void setCutoff(float cutoff);
	void setMatrix(glm::mat4 matrix);

	//Ereditato da object
	 void render(glm::mat4 renderMatrix) override;
private:
	//impostazioni luce//
	glm::vec4 position;
	short intensity;
	//tipi di luce
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	//direzione della luce
	glm::vec4 direction;
	//colore della luce RGBA
	glm::vec4 color;
	//sottotipo luce(directional, omni, spotlight)
	SubType subType;
	float cutoff;
	float radius;
	float angle;
	bool isActive = false;
};
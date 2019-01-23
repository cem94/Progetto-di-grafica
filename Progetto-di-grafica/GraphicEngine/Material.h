#pragma once

/**
* Contains all the parameters necessary to define a material. It enables to change material properties and it
* is responsible for transferring its settings to OpenGL through the necessary methods.
*/
class  Material : public Object
{
public:
	Material();
	virtual ~Material();
	Texture* getTexture() const;
	void setTexture(Texture* texture);
	void setAmbient(glm::vec3 ambient);
	glm::vec3 getAmbient() const;
	void setDiffuse(glm::vec3 diffuse);
	glm::vec3 getDiffuse() const;
	void setSpecular(glm::vec3 specular);
	glm::vec3 getSpecular() const;
	float getShininess() const;
	void setShininess(float shininess);
	float getAlpha() const;
	void setAlpha(float alpha);
	glm::vec4 getEmissive() const;
	void setEmissive(glm::vec4 emissive);
	void setTexture(std::string textureName);
	bool hasTexture() const;
	bool isTrasparent() const;
	void activeTransparencies();
	void render(glm::mat4 renderMatrix = glm::mat4(1.0f)) override;
private:
	Texture* texture;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess = 128;
	glm::vec4 emissive;
	float alpha = 1;
};

#pragma once
/*Contains all the parameters necessary to define a material. It enables to change material properties and it is responsible for transferring its settings to OpenGL through the necessary methods.*/
class  Material : public Object
{
public:
	Material();
	virtual ~Material();
	Texture* getTexture() const;
	void setTexture(Texture* texture);
	void setAmbient(glm::vec3 ambient);
	glm::vec3 getAmbient();	
	void setDiffuse(glm::vec3 diffuse);
	glm::vec3 getDiffuse();
	void setSpecular(glm::vec3 specular);
	glm::vec3 getSpecular();
	float getShininess() const;
	void setShininess(float shininess);
	float getAlpha() const;
	void setAlpha(float alpha);
	glm::vec4 getEmissive() const;
	void setEmissive(glm::vec4 emissive);
	void setTexture(std::string textureName);
	void render(glm::mat4 renderMatrix) override;

	bool isTrasparent();
	void activeTransparencies();
private:
	Texture* texture;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess = 128;
	glm::vec4 emissive;
	float alpha = 1;
};
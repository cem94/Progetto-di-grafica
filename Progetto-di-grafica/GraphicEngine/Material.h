#pragma once
/*Contains all the parameters necessary to define a material. It enables to change material properties and it is responsible for transferring its settings to OpenGL through the necessary methods.*/
class Material : public Object
{
public:
	Material();
	virtual ~Material();
	//Getter & setter
	Texture* getTexture() const;
	void setTexture(Texture* texture);
	void setAmbient(glm::vec4 ambient);
	glm::vec4 getAmbient();
	void setDiffuse(glm::vec4 diffuse);
	glm::vec4 getDiffuse();
	void setSpecular(glm::vec4 specular);
	glm::vec4 getSpecular();
	//ereditato da Object
	void render(glm::mat4 renderMatrix) override;
	Type getType() const override;
	float getShininess() const;
	void setShininess(float shininess);
	//TODO completare
	/*float getAlpha() const;
	void setAlpha(float alpha);*/
	glm::vec4 getEmissive() const;
	void setEmissive(glm::vec4 emissive);
private:
	Texture* texture;
	//componenti materiale
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	//specular exponent
	float shininess = 128;
	//Emissive Lighting is light that is emitted by an object such as a light bulb.
	glm::vec4 emissive;
	//TODO capire a cosa serve credo sia per le trasparenzes
	/*float alpha = 1;*/
};


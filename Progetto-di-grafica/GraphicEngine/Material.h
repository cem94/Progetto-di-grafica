#pragma once
/*Contains all the parameters necessary to define a material. It enables to change material properties and it is responsible for transferring its settings to OpenGL through the necessary methods.*/
class  Material : public Object
{
public:
	Material();
	virtual ~Material();
	//Getter & setter
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
	//TODO completare
	/*float getAlpha() const;
	void setAlpha(float alpha);*/
	glm::vec4 getEmissive() const;
	void setEmissive(glm::vec4 emissive);
	void setTexture(const char * textureName);
	//ereditato da Object
	void render(glm::mat4 renderMatrix) override;
	Type getType() const override;

private:
	Texture* texture;
	//componenti materiale
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	//specular exponent
	float shininess = 128;
	//Emissive Lighting is light that is emitted by an object such as a light bulb.
	glm::vec4 emissive;
	//TODO capire a cosa serve credo sia per le trasparenzes
	/*float alpha = 1;*/
};


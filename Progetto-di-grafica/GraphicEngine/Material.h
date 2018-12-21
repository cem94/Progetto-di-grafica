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
	void setDiffuse(glm::vec4 diffuse);
	void setSpecular(glm::vec4 specular);
	//ereditato da Object
	void render(glm::mat4 renderMatrix) override;
    //TODO
private:
	Texture* texture;
	//componenti materiale
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	//float shininess = 128;
};


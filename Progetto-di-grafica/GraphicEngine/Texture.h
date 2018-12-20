#pragma once

class Texture : public Object
{
public:
    Texture();
	Texture(std::string textureName);
    virtual ~Texture();
	void render(glm::mat4 rendermatrix) override;
    //TODO
private:
	//int textureId; potremmo usare direttamente l'id dell'object

};
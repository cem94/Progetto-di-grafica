#pragma once
/*This class represents a texture. It's responsible for loading data from a file into an OpenGL texture and for passing its settings to the OpenGL API. (More about in the OpenGL 3 chapter)*/
class Texture : public Object
{
public:
    Texture();
	Texture(std::string textureName);
    virtual ~Texture();
	void render(glm::mat4 rendermatrix) override;
    //TODO
private:
	unsigned int textureId; 
	//potremmo usare direttamente l'id dell'object
};
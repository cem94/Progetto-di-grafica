#pragma once
/**
 * Base class used by all the derived classes.This class is responsible for
 * keeping track of the existing objects, forcing some required API (virtual)
 * methods and providing a unique ID to each object.
 */
class LIB_API Object
{
public:
    enum Type { OBJECT = 0, CAMERA, LIGHT, MATERIAL, MESH, NODE, TEXTURE };
	int getId() const;
	void setId(int id);
	std::string getName() const;
	void setName(std::string name);
	void setType(Type type);
	Type getType() const;
    virtual void render(glm::mat4 rendermatrix) = 0;
private:
    Type type;
    int id;
    std::string name;
};

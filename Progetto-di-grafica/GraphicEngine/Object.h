#pragma once

/**
 * Base class used by all the derived classes.This class is responsible for
 * keeping track of the existing objects, forcing some required API (virtual)
 * methods and providing a unique ID to each object.
 */
class  Object
{
public:
    enum Type { OBJECT = 0, CAMERA, LIGHT, MATERIAL, MESH, NODE, TEXTURE };
    int getId() const
    {
        return id;
    };
    void setId(int objectId)
    {
        id = objectId;
    };
    std::string getName() const
    {
        return name;
    };
    void setName(std::string objectName)
    {
        name = objectName;
    };
    void setType(Type objectType)
    {
        type = objectType;
    };
    Type getType() const
    {
        return type;
    };
    virtual void render(glm::mat4 rendermatrix) = 0;
private:
    Type type;
    int id;
    std::string name;
};

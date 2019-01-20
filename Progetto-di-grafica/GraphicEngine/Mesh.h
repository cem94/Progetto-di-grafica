#pragma once
/*Class responsible for storing a single 3D object (including its vertices, texturing coordinates, and a reference to the used material). The class includes the necessary methods for transferring data to OpenGL.*/
#include "Engine.h"
class  Mesh : public Node
{
public:
    Mesh();
    virtual ~Mesh();
    Material * getMaterial() const;
    void setMaterial(Material* material);
    float getRadius();
    void setRadius(float radius);
    void setNumberOfFaces(unsigned int numberOfFaces);
    void generateVAO(float * vertexArray, float * normalArray, float * uvArray, unsigned int * indices, unsigned int vertices);
    void render(glm::mat4 renderMatrix) override;
private:
    float radius;
    unsigned int numberOfFaces;
    unsigned int* indices;
    float* vertices;
    float* normals;
    float* textureArray;
    unsigned int vertexVBO = 0;
    unsigned int normalVBO = 0;
    unsigned int uvVBO = 0;
    unsigned int indicesVBO = 0;
    unsigned int vao = 0;
    Material* material;
};

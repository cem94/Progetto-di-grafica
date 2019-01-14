#pragma once
/*Class responsible for storing a single 3D object (including its vertices, texturing coordinates, and a reference to the used material). The class includes the necessary methods for transferring data to OpenGL.*/
#include "Engine.h"
class  Mesh : public Node
{
public:
	Mesh();
	Mesh(const char* name): Node(name) {};
	virtual ~Mesh();
	//Getters & Setters

	Material * getMaterial() const;
	void setMaterial(Material* material);
	void setRadius(float radius);
	void setNumberOfFaces(unsigned int numberOfFaces);
	void setMatrix(glm::mat4 matrix);
	void generateVAO(float * vertexArray, float * normalArray, float * uvArray, unsigned int * indices, unsigned int vertices);

	std::vector<glm::vec3> getVertexes() const;
	void setVertexes(std::vector<glm::vec3> vertexes);
	std::vector<glm::vec4> getNormals() const;
	void setNormals(std::vector<glm::vec4> normals);
	std::vector<glm::vec4> getTextureCoordinates() const;
	void setTextureCoordinates(std::vector<glm::vec4> textureCoordinates);
	void setVertexOrder(std::vector<unsigned int> facesArray);
		//Ereditato da Object
	 void render(glm::mat4 renderMatrix) override;
	 Type getType() const override;
private:
	
	//Usate dall'ovo reader 1/////////////////////////////////
	/*float radius;
	//unsigned int* indices;
	unsigned int numberOfFaces;
	unsigned int* indices;
	float* vertices;
	float* normals;
	float* textureArray;

	unsigned int vertexVBO = 0;
	unsigned int normalVBO = 0;
	unsigned int uvVBO = 0;
	unsigned int indicesVBO = 0;

	//VAO
	unsigned int vao = 0;
	*/
	//////////////////////////////////////////////////
	//materiale di cui è fatta la mesh
	Material* material;
	//USATE DALL'OVO READER 1 ///
	//aggiungere coordinate texturing e vettori normali
	std::vector<unsigned int> facesArray;
	//vertici mesh
	std::vector<glm::vec3> vertexes;
	//vettori normali
	std::vector<glm::vec4> normals;
	//coordinate di texturing
	std::vector<glm::vec4> textureCoordinates;
};


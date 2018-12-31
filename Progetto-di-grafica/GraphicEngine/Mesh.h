#pragma once
/*Class responsible for storing a single 3D object (including its vertices, texturing coordinates, and a reference to the used material). The class includes the necessary methods for transferring data to OpenGL.*/
class Mesh : Node
{
public:
	Mesh();
	virtual ~Mesh();
	//Getters & Setters
	std::vector<glm::vec4> getVertexes() const;
	void setVertexes(std::vector<glm::vec4> vertexes);
	std::vector<glm::vec4> getNormals() const;
	void setNormals(std::vector<glm::vec4> normals);
	std::vector<glm::vec4> getTextureCoordinates() const;
	void setTextureCoordinates(std::vector<glm::vec4> textureCoordinates);
	Material * getMaterial() const;
	void setMaterial(Material* material);
	//Ereditato da Object
	void render(glm::mat4 renderMatrix) override;
	Type getType() const override;
private:
	//vertici mesh
	std::vector<glm::vec4> vertexes;
	//vettori normali
	std::vector<glm::vec4> normals;
	//coordinate di texturing
	std::vector<glm::vec4> textureCoordinates;
	//TODO capire a che servono
	/*float radius;
	unsigned int* indices;
	*/
	//materiale di cui è fatta la mesh
	Material* material;
	//aggiungere coordinate texturing e vettori normali
};


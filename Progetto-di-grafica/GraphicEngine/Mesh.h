#pragma once
/*Class responsible for storing a single 3D object (including its vertices, texturing coordinates, and a reference to the used material). The class includes the necessary methods for transferring data to OpenGL.*/
class Mesh : Node
{
public:
	Mesh();
	virtual ~Mesh();
	std::vector<glm::vec4> getVertexes() const;
	void setVertices(std::vector<glm::vec4> vertexes);
	Material * getMaterial() const;
	void setMaterial(Material* material);
	void render(glm::mat4 renderMatrix) override;
	//TODO
private:
	//vertici mesh
	std::vector<glm::vec4> vertexes;
	//materiale di cui è fatta la mesh
	Material* material;
	//aggiungere coordinate texturing e vettori normali
};


#pragma once
/*Class responsible for storing a single 3D object (including its vertices, texturing coordinates, and a reference to the used material). The class includes the necessary methods for transferring data to OpenGL.*/
class Mesh : Node
{
public:
    Mesh();
    virtual ~Mesh();

    std::vector<glm::vec4> getVertexes() const;

     void render(glm::mat4 renderMatrix) override;
    //TODO: getUsedMaterials
	 Material * getMaterial() const;

private:
	//vertici mesh
    std::vector<glm::vec4> vertexes;
	//materiale di cui è fatta la mesh
	Material* material;
	//aggiungere coordinate texturing e vettori normali
};


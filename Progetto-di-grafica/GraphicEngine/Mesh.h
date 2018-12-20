#pragma once

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
    std::vector<glm::vec4> vertexes;
	//materiale di cui è fatta la mesh
	Material* material;

};


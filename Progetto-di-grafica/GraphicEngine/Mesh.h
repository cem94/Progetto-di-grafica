#pragma once

class Mesh : Node
{
public:
    Mesh();
    virtual ~Mesh();

    std::vector<glm::vec4> getVertexes() const;
    void renderMesh();
    //TODO: getUsedMaterials

    // Ereditato tramite EngineNode
    virtual glm::vec4 getPosition() const override;

private:
    std::vector<glm::vec4> vertexes;
};


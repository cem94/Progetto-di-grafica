#pragma once

class Light : public Node
{
public:
    Light();
    virtual ~Light();

    short getIntensity() const;
    void setIntensity(short intensity);
    void renderLight();
    //TODO: capire come fare
    void typeLight();

    // Ereditato tramite EngineNode
    virtual glm::vec4 getPosition() const override;

private:
    short intensity;
    glm::vec4 position;
};


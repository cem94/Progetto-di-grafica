#pragma once

/**
* Light class that implements the main types of light introduced in the course.
* This class includes the necessary methods for applying its settings to OpenGL.
*/
class  Light : public Node
{
public:
    Light();
    Light(std::string name);
    virtual ~Light();
    enum Subtype { OMNI, SPOTLIGHT, DIRECTIONAL };
    void setAmbient(glm::vec4 ambient);
    void setDiffuse(glm::vec4 diffuse);
    void setSpecular(glm::vec4 specular);
    Subtype getSubtype() const;
    void setSubtype(Subtype subtype);
    int getLightNumber() const;
    void setLightNumber(int lightNumber);
    void setColor(glm::vec4 color);
    void setPosition(glm::vec4 position);
    glm::vec3 getDirection();
    void setDirection(glm::vec4 direction);
    void setAngle(float angle);
    float getAngle() const;
    float getRadius() const;
    void setRadius(float radius);
    float getCutoff() const;
    void setCutoff(float cutoff);
    void enableLight();
    void disableLight();
    void changeState();
    void render(glm::mat4 renderMatrix) override;
private:
    glm::vec4 color;
    glm::vec4 direction;
    glm::vec4 position;
    const float intensity = 0.9f;
    const float attenuation = 0.001f;
    const float shininess = 128.0f;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    Subtype subtype;
    float cutoff;
    float radius;
    float angle;
    bool isActive = false;
    int lightNumber;
    static int numberOfLights;
};

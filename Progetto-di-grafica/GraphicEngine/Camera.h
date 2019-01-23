#pragma once

/**
* This class represents a camera. Settings should comprise both orthographic and
* perspective projections, and the necessary math to retrieve the camera
* inverse matrix.
*/
class  Camera : public Node
{
public:
    Camera();
    virtual ~Camera();
    void setProjectionMatrix(glm::mat4 projection);
    void setMovable(bool movable);
    bool getMovable() const;
    void render(glm::mat4 renderMatrix) override;
private:
    glm::mat4 projectionMatrix;
    bool movable = false;
};

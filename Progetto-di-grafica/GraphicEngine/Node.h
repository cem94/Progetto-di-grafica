#pragma once

class  Node : public Object
{
public:
    Node();
    virtual ~Node();

    Node* getParent() const;
    void setParent(Node* parent);
    Node* getChildren() const;
    void setChildren(Node* children);

    //TODO: controllare se vec4 o vec3
    virtual glm::vec4 getPosition() const = 0;
	glm::mat4 getMatrix() const;
	void setMatrix(glm::mat4 matrix);

private:
    Node* parent;
    Node* children;
	glm::mat4 matrix;
};
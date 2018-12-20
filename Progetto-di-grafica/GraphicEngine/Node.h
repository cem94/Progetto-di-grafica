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

	glm::mat4 getMatrix() const;
	void setMatrix(glm::mat4 matrix);
	int getChildrenSize() const;
	 void render(glm::mat4 rendermatrix) override;

private:
	//struttura gerarchica
    Node* parent;
    Node* children;
	//posizione
	glm::mat4 matrix;
};
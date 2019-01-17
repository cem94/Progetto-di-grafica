#pragma once
/*Extends the Object class with the required functions to locate the object in the 3D space (through a matrix) and in a hierarchy (through a hierarchical structure).*/
class Node : public Object
{
public:
	Node();
	virtual ~Node();
	Node* getParent() const;
	void setParent(Node* parent);
	std::vector<Node*> getChildren() const;
	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 matrix);
	void insert(Node *node);
	void remove(int position);
	void remove(Node* node);
	int getChildrenSize() const;
	void setChildrenSize(unsigned int size);
	glm::mat4 getFinalMatrix();
	// Lo usiamo quando dobbiamo costruire l'albero, non potendo usare getChildrenSize();
    int getCapacity() const;
	virtual void render(glm::mat4 rendermatrix) override;
private:
	Node* parent{ nullptr };
	std::vector<Node*> children;
	glm::mat4 matrix;
};
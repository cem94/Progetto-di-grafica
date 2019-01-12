#pragma once
/*Extends the Object class with the required functions to locate the object in the 3D space (through a matrix) and in a hierarchy (through a hierarchical structure).*/
class Node : public Object
{
public:
	Node();
	Node(const char* name);
	Node(const char* name, Type type);
	virtual ~Node();
	//Getters & Setters
	Node* getParent() const;
	void setParent(Node* parent);
	std::vector<Node*> getChildren() const;
	void setChildren(std::vector<Node*> children);
	glm::mat4 getMatrix() const;
	void setMatrix(glm::mat4 matrix);
	//methods for the hierarchical structure
	void insert(Node *node);
	void remove(int position);
	void remove(Node* node);
	int getChildrenSize() const;
	void setChildrenSize(unsigned int size);
	//ereditato da Object
	virtual Type getType() const override;
	virtual void render(glm::mat4 rendermatrix) override;
private:
	//struttura gerarchica//
	Node* parent;
	std::vector<Node*> children;
	//matrice di posizione
	glm::mat4 matrix;
<<<<<<< HEAD
	unsigned int size;
=======

	int childrenSize=0;

>>>>>>> 2ce52d2d1083d3f095fb395bf382bceb26b9aa0e
};
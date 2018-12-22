#pragma once
/*Extends the Object class with the required functions to locate the object in the 3D space (through a matrix) and in a hierarchy (through a hierarchical structure).*/
class  Node : public Object
{
public:
	Node();
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
	//ereditato da Object
	void render(glm::mat4 rendermatrix) override;
private:
	//struttura gerarchica//
	Node* parent;
	//Per ottimizzare si potrebbe capire quanti figli avrà e preallocarlo prima di riempirlo
	std::vector<Node*> children;
	//matrice di posizione
	glm::mat4 matrix;
};
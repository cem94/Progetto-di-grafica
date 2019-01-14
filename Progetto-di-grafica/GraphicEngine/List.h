#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/
class List : public Object
{
public:
	List();
	virtual ~List();
	std::list<Node*> getList() const;
	void setList(std::list<Node*> list);
	void add(Node* node, glm::mat4 matrix);
	void remove(int position);
	Node* at(int position);
	//Ereditato da object
	 void render(glm::mat4 renderMatrix) override;
	 Type getType() const override;
private:
	//credo che la lista sia più efficente -> controllare
	std::list<Node*> list;
};
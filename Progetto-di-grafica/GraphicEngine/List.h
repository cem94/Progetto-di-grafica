#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/

class List : public Object
{
public:
	List();
	virtual ~List();
	std::vector<Node*> getList() const;
	// se si riserva la memoria, la velocità aumenta.
    void reserve(int dim);
	void setList(std::vector<Node*> list);
	void add(Node* node);
	void remove(int position);
	Node* at(int position);
	void insert(std::vector<Node*> elements);
	void render(glm::mat4 renderMatrix) override;
private:
	// Vector nel nostro caso è più veloce e pure il sore consiglia di usarlo.
	// https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl
	// https://baptiste-wicht.com/posts/2017/05/cpp-containers-benchmark-vector-list-deque-plf-colony.html
	std::vector<Node*> vector;
};
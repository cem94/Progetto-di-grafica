#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/

class  List : public Object
{
public:
    List();
    List(Node *root);
    virtual ~List();
    std::vector<Node*> getList() const;
    // se si riserva la memoria, la velocità aumenta.
    void reserve(int dimension);
    void setList(std::vector<Node*> list);
    void add(Node* node);
    void remove(int position);
    Node* at(int position);
    void insert(std::vector<Node*> elements);
	void transparentPreRender(Material *material);
    void render(glm::mat4 renderMatrix) override;
     int size();
	void getTreeAsList(Node *root, std::vector<Node*>& nodes);
	void sort(Node * root);
	void setIsRefletcion(bool isReflection);
    bool getIsReflection();
private:
    std::vector<Node*> list;
	bool isReflection = false;
};

#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/

class LIB_API List : public Object
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
	void transparentPreRender(Material *material, glm::mat4 renderMatrix);
    void render(glm::mat4 renderMatrix=glm::mat4(1.0f)) override;
    unsigned int size();
	void getTreeAsList(Node *root, std::vector<Node*>& nodes);
	void sort(Node * root);
private:
    //ok l'ho solo rinominato in list visto che la classe rappresenta una lista
    std::vector<Node*> list;
};

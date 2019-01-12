#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/
#include <list>
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
	void render(glm::mat4 renderMatrix) override;
	Node* findByName(std::string name) {/*TODO*/ };
	Node* findByID(int id) {/*TODO*/ };
	virtual Type getType() const override;
private:
	//credo che la lista sia più efficente -> controllare
	std::list<Node*> objects;
};

/*• One same element (mesh, light, etc.) can be rendered multiple times at different coordinates and/or using different parameters.
• Instead of directly rendering an element, you can store a list of objects with specific properties (e.g., using a different matrix and material each time):
	– The list is parsed and each entry is rendered using the parameters stored in the list:
• The list can also be sorted to render light sources first, then meshes.
	– In addition, the list can be rendered from a specific point of view by passing a camera:
• Each matrix in the list is multiplied by the inverse of the camera matrix.
• You can re-render the same scene from different points of view without refreshing the list’s entries.*/
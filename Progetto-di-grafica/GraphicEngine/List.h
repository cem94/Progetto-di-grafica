#pragma once
/*Contains a list of instances, each one with its own properties(such as position, material, etc.).Matrices are stored in world coordinates after being evaluated according to their hierarchy.*/
class List : public Object
{
public:
	//classe che contiene l'oggetto e la matrice in world coordinates
	//TODO possiamo rimuovere element secondo me è usare Liste di Node ( salvando li la matrice) ma non sono sicuro // -> CHIEDERE
	class Element
	{
	public:
		Element(Object* object, glm::mat4 matrix)
			:object{ object }, matrix{ matrix }
		{
		}
		Object * object;
		glm::mat4 matrix;
		glm::mat4 getMatrix()
		{
			return this->matrix;
		}
		Object* getNode()
		{
			return this->object;
		}
	};
	List();
	virtual ~List();
	std::vector<Element*> getList() const;
	void setList(std::vector<Element*> list);
	void add(Object* node, glm::mat4 matrix);
	void remove(int position);
	Element* at(int position);
	void render(glm::mat4 renderMatrix) override;
	//non so chi ha scritto questi metodi
	Element* findByName(std::string name) {/*TODO*/ };
	Element* findByID(int id) {/*TODO*/ };
private:
	std::vector<Element*> objects;
};

/*• One same element (mesh, light, etc.) can be rendered multiple times at different coordinates and/or using different parameters.
• Instead of directly rendering an element, you can store a list of objects with specific properties (e.g., using a different matrix and material each time):
	– The list is parsed and each entry is rendered using the parameters stored in the list:
• The list can also be sorted to render light sources first, then meshes.
	– In addition, the list can be rendered from a specific point of view by passing a camera:
• Each matrix in the list is multiplied by the inverse of the camera matrix.
• You can re-render the same scene from different points of view without refreshing the list’s entries.*/
#include "Engine.h"
#include <GL/freeglut.h>

/**
 * List constructor
 */
List::List()
{
}

List::List(Node * root)
{
	getTreeAsList(root, list);
}

/**
* List Destructor
*/
List::~List()
{
}

/**
 * Getter for list
 * @return list
 */
std::vector<Node*> List::getList() const
{
    return this->list;
}
/**
 * Setter for list
 * @param  list
 */
void List::setList(std::vector<Node*> list)
{
    this->list = list;
}
/**
* Reserve memory for list
* @param  size how much we want to reserve
*/
void List::reserve(int size)
{
    this->list.reserve(size);
}

/**
 * Add a node to the list
 * @param  node the node we want to add
 */
void List::add(Node* node)
{
    this->list.push_back(node);
}

/**
 * Removes a node from the list given its position
 * @param  position
 */
void List::remove(int position)
{
    list.erase(list.begin() + position);
}

/**
 * Return the element at the position passed as an argument or nullptr if out of range
 * @param  position the position of the desired element
 * @return if the range is valid it returns the requested node, otherwise it return nullptr
 */
Node* List::at(int position)
{
    // non vogliamo che lanci un eccezione.
    if (position < this->list.size() && position >= 0)
    {
        return list.at(position);
    }
    return nullptr;
}
/**
 * insert a list of elements at the end of our list
 * @param  list of elements to add
 */
void List::insert(std::vector<Node*> elements)
{
    if (elements.size() == 0)
        printf("Nothing to insert\n");//TODO remove
    else
        list.insert(list.end(), elements.begin(), elements.end());
}
/**
 * Give the size of the list
 * @return size of the list
 */
unsigned int List::size()
{
    return (unsigned int)this->list.size();
}

void List::getTreeAsList(Node *root, std::vector<Node*>& nodes) {
	const int size = root->getChildrenSize();
	nodes.push_back(root);
	for (int i = 0; i < size; i++) {
		getTreeAsList(root->getChildren().at(i), nodes);
	}
}

 void List::sort(Node * root)
 {
	/*  std::vector<Node*> allNodes;
	 getTreeAsList(root,allNodes);*/
	 //I create a vector of pure nodes
	 std::vector<Node*> pureNodes;

	 //I create a vector of lights
	 std::vector<Light*> lights;

	 //I create a vector of meshes
	 std::vector<Mesh*> meshes;

	 for (int i = 0; i < list.size(); i++) {
		 if (list.at(i)->getType() == Object::NODE) {
			 pureNodes.push_back(list.at(i));
			 continue;
		 }
		 if (list.at(i)->getType() == Object::LIGHT) {
			 lights.push_back(dynamic_cast<Light*>(list.at(i)));
			 continue;
		 }
		 if (list.at(i)->getType() == Object::MESH) {
			 meshes.push_back(dynamic_cast<Mesh*>(list.at(i)));
			 continue;
		 }
	 }
	 //Svuoto lista
	 list.clear();
	 //TODO inserisco elementi in ordine
	 for (int i = 0; i < pureNodes.size(); i++) {
		 list.push_back(pureNodes.at(i));
	 }
	 for (int i = 0; i < lights.size(); i++) {
		 list.push_back(lights.at(i));
	 }
	 for (int i = 0; i < meshes.size(); i++) {
		 list.push_back(meshes.at(i));
	 }
 }
/**
* support method for transparent render
* @param material and render matrix
*/
void List::transparentPreRender(Material *material, glm::mat4 renderMatrix)
{
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	// At first render back faces
	glCullFace(GL_FRONT);
	material->render(renderMatrix);
	// Then render front faces
	glCullFace(GL_BACK);
	material->render(renderMatrix);
	// Enabled z-buffer write
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
}
/**
 * Render for list 
 * @param  matrix render matrix (not used)
 */
void List::render(glm::mat4 matrix)
{
	glm::mat4 camera = Engine::getInstance().getCurrentCamera()->getMatrix();
	for (Node* n : list)
	{
		glm::mat4 renderMatrix = n->getFinalMatrix();

		if (n->getType() == Object::Type::MESH)
		{
			Mesh* m = static_cast<Mesh*>(n);
			if (m->getMaterial() != nullptr)
			{
				if (m->getMaterial()->isTrasparent())
				{
					transparentPreRender(m->getMaterial(), renderMatrix);
				}
			}
		}
		n->render(camera * renderMatrix);

		//n->render(renderMatrix);
	}
}

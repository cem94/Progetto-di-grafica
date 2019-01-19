#include "Engine.h"

/**
 * List constructor
 */
List::List()
{
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

//TODO remove
/**
 * insert a list of elements at the end of our list
 * @param  list of elements to add
 */
void List::insert(std::vector<Node*> elements)
{
	if (elements.size() == 0)
		printf("Nothing to insert\n");
    else
		list.insert(list.end(), elements.begin(), elements.end());
}
/**
 * Render for list (empty)
 * @param  renderMatrix render matrix
 */
void List::render(glm::mat4 renderMatrix)
{
}
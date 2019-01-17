#include "Engine.h"

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
List::List()
{
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
List::~List()
{
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
std::vector<Node*> List::getList() const
{
	return this->vector; 
}

/**
* Comment
* @param  name1
* @param2 name2
* @return what it returns
*/
void List::reserve(int dim) 
{ 
	this->vector.reserve(dim); 
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::setList(std::vector<Node*> vector)
{
	this->vector = vector;
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
//aggiunge oggetto a lista istanze
void List::add(Node* node) 
{
	this->vector.push_back(node);
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::remove(int position)
{ 
	vector.erase(vector.begin() + position); 
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node* List::at(int position) 
{
	// non vogliamo che lanci un eccezione.
	if (position < this->vector.size() && position >= 0)
	{
		return vector.at(position);
	}
	return nullptr;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::insert(std::vector<Node*> elements)
{
	if (elements.size() == 0)
		printf("Nothing to insert\n");
    else
		vector.insert(vector.end(), elements.begin(), elements.end());
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::render(glm::mat4 renderMatrix)
{
}
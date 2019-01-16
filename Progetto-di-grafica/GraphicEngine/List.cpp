#include "Engine.h"
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
List::List(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
List::~List(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
std::list<Node*> List::getList() const{	return this->list;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::setList(std::list<Node*> list){	this->list = list;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
//aggiunge oggetto a lista istanze
void List::add(Node* node) 
{
	this->list.push_back(node);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::remove(int position)
{
	std::list<Node*>::iterator it;
	advance(it, position);
	list.erase(it);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Node* List::at(int position) 
{
	if (position < this->list.size())
	{
		std::list<Node*>::iterator it;
		advance(it, position);
		return *it;
	}
	return nullptr;
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::insert(std::list<Node*> elements)
{
	if (elements.size() == 0) {
		printf("Nothing to insert\n");
	}else
		list.insert(list.begin(), elements.begin(), elements.end());
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void List::render(glm::mat4 renderMatrix){}
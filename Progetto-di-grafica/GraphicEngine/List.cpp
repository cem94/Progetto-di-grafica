#include "Engine.h"

List::List(){}

List::~List(){}

std::list<Node*> List::getList() const{	return this->list;}

void List::setList(std::list<Node*> list){	this->list = list;}

//aggiunge oggetto a lista istanze e salva matrice(in worldCoordinates)
void List::add(Node* node) 
{
	//node->setMatrix(matrix);
	this->list.push_back(node);
}

void List::remove(int position)
{
	std::list<Node*>::iterator it;
	advance(it, position);
	list.erase(it);
}

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



void List::insert(std::list<Node*> elements)
{
	if (elements.size() == 0) {
		printf("Nothing to insert\n");
		return;
	}
	list.insert(list.begin(), elements.begin(), elements.end());
}

void List::render(glm::mat4 renderMatrix){}

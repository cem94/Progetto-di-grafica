#include "Engine.h"

List::List(){}

List::~List(){}

std::list<Node*> List::getList() const{	return this->list;}

void List::setList(std::list<Node*> list){	this->list = list;}

//aggiunge oggetto a lista istanze e salva matrice(in worlCoordinates)
void List::add(Node* node, glm::mat4 matrix) 
{
	node->setMatrix(matrix);
	this->list.push_back(node);
}

void List::remove(int position)
{
	std::list<Node*>::iterator iterator;
	advance(iterator, position);
	this->list.erase(iterator);
}

Node* List::at(int position)
{
	if (position < this->list.size())
	{
		std::list<Node*>::iterator iterator;
		advance(iterator, position);
		return *iterator;
	}
	return nullptr;
}

<<<<<<< HEAD
void List::render(glm::mat4 renderMatrix)
{
/*	std::list<Node*> render = this->getList();
	for (std::list<Node*>::iterator it = render.begin(); it != render.end(); ++it)
	{
		glm::mat4 renderMatrix = (*it)->getMatrix();
		if ((*it)->getType() == Object::Type::MESH)
		{
			Mesh* mesh = (Mesh*)(*it);
			if (mesh->getMaterial() != nullptr)
			{
				//renderizzo materiale mesh
				mesh->getMaterial()->render(renderMatrix);
				//renderizzo textures mesh TODO
				Texture* t = mesh->getMaterial()->getTexture();
				t->render(renderMatrix);
			}
		}
		//renderizzo elementi
		std::string s = (*it)->getName();
		//	printf("Rendering %s\n", s.c_str());
		(*it)->render(currentCamera->getMatrix()*renderMatrix);
	}*/

	//Empty
}
//non ritorna nulla -> tipo lista non c'è
=======
void List::render(glm::mat4 renderMatrix){}

//There isn't light type
>>>>>>> 3c60b6a312a4571c0fbe2329b4569aad649a2e8e
Object::Type List::getType() const
{
	return Object::NONE;
}

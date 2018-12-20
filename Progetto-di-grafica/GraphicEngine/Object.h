#pragma once

class Object
{
public:
    Object() {};
    virtual ~Object();
    int getID() const;
    int generateID();
    std::string getName() const;
    void setName(std::string name);
    Object* findByName(std::string name);
    Object* findByID(int id);
    //TODO: Mandatory

private:
	//Il compilatore si lamenta se stanno qua TODO spostare
	//warning C4251 : 'Object::name' : class 'std::basic_string<char,std::char_traits<char>,std::allocator<char>>' needs to have dll - interface to be used by clients
   // std::vector<Object> listObject;
    //int id;
    //std::string name;
};
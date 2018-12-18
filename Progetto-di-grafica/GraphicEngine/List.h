#pragma once
#include "Object.h"

class List : public Object
{
public:
    List();
    virtual ~List();

    std::vector<Object> getList();
    void addObject(Object obj);
    void removeObject(Object obj);
    void renderList();

private:
    std::vector<Object> objects;
};


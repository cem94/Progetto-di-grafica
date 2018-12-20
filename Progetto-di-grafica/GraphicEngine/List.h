#pragma once

class List : public Object
{
public:
    List();
    virtual ~List();

    std::vector<Object*> getList() const;
    void addObject(Object* node);
    void removeObject(Object* node);
	void setList(std::vector<Object*> list);
	void render(glm::mat4 renderMatrix) override;

private:
    std::vector<Object*> objects;
};


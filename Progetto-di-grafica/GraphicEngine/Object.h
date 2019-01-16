#pragma once
/* Base class used by all the derived classes.This class is responsible for
 * keeping track of the existing objects, forcing some required API (virtual)
 * methods and providing a unique ID to each object. */

class  Object {
public:
	/**
	* Comment
	* @param  name1
	* @param2 name2
	* @return what it returns
	 */
	enum Type { OBJECT = 0, CAMERA, LIGHT, MATERIAL, MESH, NODE, TEXTURE };
	/**
	* Comment
	* @param  name1
	* @param2 name2
	 * @return what it returns
	*/
	int getId() const { return this->id; };
	void setId(int id)  { this->id=id; };
	/**
	* Comment
	* @param  name1
	* @param2 name2
	* @return what it returns
	*/
	std::string getName() const { return this->name; };
	/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
	void setName(std::string name) { this->name = name; };
	/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
	void setType(Type type) { this->type = type; }
	/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
	virtual void render(glm::mat4 rendermatrix) = 0;
	/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
	Type getType() const { return type; };
private:
	Type type;
	int id;
	std::string name;
};
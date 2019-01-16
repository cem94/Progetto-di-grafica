#include "Engine.h"
#include <GL/glew.h>
// FreeGLUT:
#include <GL/freeglut.h>
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Mesh::Mesh(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Mesh::~Mesh(){}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Mesh::generateVAO(float * vertexes, float * normals, float * uvArray, unsigned int * indices, unsigned int vertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), vertexes, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), normals, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 2 * sizeof(float), uvArray, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfFaces * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindVertexArray(0);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Material * Mesh::getMaterial() const{	return material;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Mesh::setMaterial(Material * material){	this->material = material;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Mesh::setRadius(float radius){	this->radius = radius;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Mesh::setNumberOfFaces(unsigned int numberOfFaces){	this->numberOfFaces = numberOfFaces;}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Mesh::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numberOfFaces * 3, GL_UNSIGNED_INT, nullptr);
}
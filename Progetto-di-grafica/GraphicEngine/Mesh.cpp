#include "Engine.h"
//#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

std::vector<glm::vec3> Mesh::getVertexes() const
{
	return this->vertexes;
}

void Mesh::setVertexes(std::vector<glm::vec3> vertexes)
{
	this->vertexes = vertexes;
}
//TODO provvisorio: capire come farlo meglio
void Mesh::setMatrix(glm::mat4 matrix)
{
	Node::setMatrix(matrix);
}
void Mesh::generateVAO(float * vertexArray, float * normalArray, float * uvArray, unsigned int * indices, unsigned int vertices)
{
	/*glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), vertexArray, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), normalArray, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 2 * sizeof(float), uvArray, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, nullptr);

	glGenBuffers(1, &indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfFaces * 3 * sizeof(unsigned int), indicesArray, GL_STATIC_DRAW);


	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindVertexArray(0);
	*/
}

void Mesh::setVertexOrder(std::vector<unsigned int> facesArray)
{
	this->facesArray = facesArray;
}

std::vector<glm::vec4> Mesh::getNormals() const
{
	return this->normals;
}

void Mesh::setNormals(std::vector<glm::vec4> normals)
{
	this->normals = normals;
}

std::vector<glm::vec4> Mesh::getTextureCoordinates() const
{
	return this->textureCoordinates;
}

void Mesh::setTextureCoordinates(std::vector<glm::vec4> textureCoordinates)
{
	this->textureCoordinates = textureCoordinates;
}

Material * Mesh::getMaterial() const
{
	return material;
}

void Mesh::setMaterial(Material * material)
{
	this->material = material;
}

/*void Mesh::setRadius(float radius)
{
	this->radius = radius;
}

void Mesh::setNumberOfFaces(unsigned int numberOfFaces)
{
	this->numberOfFaces = numberOfFaces;
}
*/
void Mesh::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, numberOfFaces * 3, GL_UNSIGNED_INT, nullptr);
}

Object::Type Mesh::getType() const
{
	return MESH;
}

/*void Mesh::generateVAO(float * vertexArray, float * normalArray, float * uvArray, unsigned int * indicesArray, unsigned int vertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), vertexArray, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 3 * sizeof(float), normalArray, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, nullptr);
	glGenBuffers(1, &uvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * 2 * sizeof(float), uvArray, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
	glGenBuffers(1, &indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfFaces * 3 * sizeof(unsigned int), indicesArray, GL_STATIC_DRAW);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindVertexArray(0);
}*/
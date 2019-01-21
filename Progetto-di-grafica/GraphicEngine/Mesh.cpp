#include "Engine.h"
#include <GL/glew.h>
// FreeGLUT:
#include <GL/freeglut.h>

/**
 * Mesh constructor
 */
Mesh::Mesh()
{
}

/**
 * Mesh destructor
 */
Mesh::~Mesh()
{
}

/**
 * Generate vao (vertex array objects)
 * @param  vertexes vertexes array
 * @param normals normals vertexes array
 * @param uvArray uv vertexes array
 * @param indices indices array
 * @param numberOfVertexes number of vertexes
 */
void Mesh::generateVAO(float * vertexes, float * normals, float * uvArray, unsigned int * indices, unsigned int numberOfVertexes)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	//vertex vbo
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertexes * 3 * sizeof(float), vertexes, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
	//normals
    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertexes * 3 * sizeof(float), normals, GL_STATIC_DRAW);
    glNormalPointer(GL_FLOAT, 0, nullptr);
	//array uv
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertexes * 2 * sizeof(float), uvArray, GL_STATIC_DRAW);
    glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
	//indices vbo
    glGenBuffers(1, &indicesVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfFaces * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindVertexArray(0);
}

/**
 * Getter for material
 * @return mesh material
 */
Material * Mesh::getMaterial() const
{
    return material;
}

/**
 * Setter for material
 * @param  material mesh material
 */
void Mesh::setMaterial(Material * material)
{
    this->material = material;
}

/**
* Getter for radius
* @return mesh radius
*/
float Mesh::getRadius()
{
    return this->radius;
}

/**
 * Setter for radius
 * @param  radius mesh radius
 */
void Mesh::setRadius(float radius)
{
    this->radius = radius;
}

/**
 * Setter for numberOfFaces
 * @param  numberOfFaces number of mesh faces
 */
void Mesh::setNumberOfFaces(unsigned int numberOfFaces)
{
    this->numberOfFaces = numberOfFaces;
}
/**
 * Render for mesh
 * @param  mesh render matrix
 */
void Mesh::render(glm::mat4 renderMatrix)
{
	//glm::mat4 camera = Engine::getInstance().getCurrentCamera()->getMatrix();
	glLoadMatrixf(glm::value_ptr( renderMatrix));
	//glLoadMatrixf(glm::value_ptr(camera * renderMatrix));
	material->render();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numberOfFaces * 3, GL_UNSIGNED_INT, nullptr);
}

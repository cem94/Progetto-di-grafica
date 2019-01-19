#include "Engine.h"

//FreeGlut
#include <GL/freeglut.h>

/**
 * Camera constructor
 */
Camera::Camera()
{
}

/**
 * Camera destructor
 */
Camera::~Camera()
{
}

/**
 * Setter for projection matrix
 * @param  projection projection matrix
 */
void Camera::setProjectionMatrix(glm::mat4 projection)
{
	this->projectionMatrix = projection;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Render camera rendering method
 * @param  render matrix
 */
void Camera::render(glm::mat4 renderMatrix)
{
	glLoadMatrixf(glm::value_ptr(renderMatrix));
}

/**
 * Setter for movable
 * @param  movable boolean value (true if movable false otherwise)
*/
void Camera::setMovable(bool movable)
{
	this->movable = movable;
}

/**
 * Getter for movable
 * @return movable value (true if movable false otherwise)
 */
bool Camera::getMovable()
{
	return movable;
}
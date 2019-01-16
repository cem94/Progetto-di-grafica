#include "Engine.h"

//FreeGlut
#include <GL/freeglut.h>
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Camera::Camera()
{
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
Camera::~Camera()
{
}

/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Camera::setProjectionMatrix(glm::mat4 projection)
{
	this->projectionMatrix = projection;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}
/**
 * Comment
 * @param  name1
 * @param2 name2
 * @return what it returns
 */
void Camera::render(glm::mat4 renderMatrix)
{	
	glLoadMatrixf(glm::value_ptr(renderMatrix));
}
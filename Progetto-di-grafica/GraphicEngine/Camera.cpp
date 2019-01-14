#include "Engine.h"

//FreeGlut
#include <GL/freeglut.h>

Camera::Camera(){}

Camera::~Camera(){}

glm::mat4 Camera::inverseCamera() const {	return glm::inverse(getMatrix());}

void Camera::setProjectionMatrix(glm::mat4 projection)
{
	this->projectionMatrix = projection;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setMatrix(glm::mat4 matrix){	Node::setMatrix(matrix);}

void Camera::render(glm::mat4 renderMatrix){	glLoadMatrixf(glm::value_ptr(renderMatrix));}

//Node::Type Camera::getType() const{		return CAMERA;}
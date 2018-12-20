#include "Engine.h"

//FreeGlut
#include <GL/freeglut.h>

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::createCamera()
{
}

void Camera::moveCamera(glm::mat4 matrix)
{
}

void Camera::zoomCamera(const int zoom)
{
}
//ritorna l'inversa della matrice corrente
glm::mat4 Camera::inverseCamera() const
{
	return glm::inverse(getMatrix());
}

void Camera::typeCamera()
{
}
//setta la matrice di proiezione della camera
void Camera::setProjectionMatrix(glm::mat4 projection)
{
	this->projectionMatrix = projection;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}


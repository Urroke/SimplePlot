#include "../headers/Camera.h"

Camera::Camera()
{
	
}

Camera& Camera::operator=(Camera const&)
{
	throw "Forbidden";
}

void Camera::lookAt(const Point3d& position, const Point3d& target, const Vector3d& refAxis)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	gluLookAt (	position.x, position.y, position.z,
				target.x,	target.y,	target.z,
				refAxis.x,	refAxis.y,	refAxis.z);
	glutPostRedisplay();
	//glutSwapBuffers();
}

void Camera::update()
{
	Vector3d vector(0, 0, 1), direct2target = tfm.rotation * vector, up(0, 1, 0);
	up = tfm.rotation * up;
	Point3d target = tfm.position + direct2target;
	lookAt(tfm.position, target, up);
}

#include "../headers/Camera.h"

Camera::Camera()
{
	
}

Camera& Camera::operator=(Camera const&)
{
	throw "Forbidden";
}

//Rotate body in local coordinate system
void Camera::rotateBy(const Vector3d& vec)
{
	Matrix rotate = tfm.getRotation(vec.y, Vector3d(0, 1, 0));
	tfm.refAxis = rotate * tfm.refAxis;
	tfm.directionAxis = rotate * tfm.directionAxis;
	tfm.rotateBy(vec.y, Vector3d(0, 1, 0));
	tfm.rotateBy(vec.x, tfm.refAxis);
	//rotateBy(vec.z, refAxis.multiply(directionAxis));
}

void Camera::lookAt(const Point3d& position, const Point3d& target, const Vector3d& refAxis)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt (	position.x, position.y, position.z,
				target.x,	target.y,	target.z,
				refAxis.x,	refAxis.y,	refAxis.z);
	glutPostRedisplay();
}

void Camera::update()
{
	Vector3d vector(0, 0, 1), direct2target = tfm.rotation * vector, up(0, 1, 0);
	up = tfm.rotation * up;
	Point3d target = tfm.position + direct2target;
	lookAt(tfm.position, tfm.position + tfm.refAxis.multiply(tfm.directionAxis), tfm.directionAxis);
}

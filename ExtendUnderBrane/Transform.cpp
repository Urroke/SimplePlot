#include "Transform.h"
#include "cmath"

Transform::Transform()
{
	position = Point3d(0, 0, 0);
	setRotation(0, Vector3d(0, 0, 0));
	scale = 1.;
}

Transform::Transform(const Point3d& position, const Matrix& rotation, double scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}
void Transform::setScale(double scale)
{
	this->scale = scale;
}
void Transform::scaleTo(double mult)
{
	scale *= mult;
}
void Transform::translateTo(const Vector3d& vec)
{
	position += vec;
}
void Transform::setPosition(const Point3d& position)
{
	this->position = position;
}
void Transform::setRotation(double a, const Vector3d& vec)
{
	Vector3d d = vec.normal();
	double cosa = std::cos(a);
	double cosa1 = 1 - cosa;
	double sina = std::sin(a);
	rotation[0][0] = cosa + d.x * d.x*cosa1;
	rotation[0][1] = d.x*d.y*cosa1 - d.z*sina;
	rotation[0][2] = d.x*d.z*cosa1 + d.y*sina;
	rotation[1][0] = d.x*d.y*cosa1 + d.z*sina;
	rotation[1][1] = cosa + d.y*d.y*cosa1;
	rotation[1][2] = d.y*d.z*cosa1 - d.x*sina;
	rotation[2][0] = d.x*d.z*cosa1 - d.y*sina;
	rotation[2][1] = d.y*d.z*cosa1 + d.x*sina;;
	rotation[2][2] = cosa + d.z*d.z*cosa1;
}
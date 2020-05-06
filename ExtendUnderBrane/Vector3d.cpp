#include "Vector3d.h"


Vector3d::Vector3d()
{
	x = y = z = 1;
}

Vector3d::Vector3d(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3d::Vector3d(const Vector3d& vector)
{
	*this = vector;
}

Vector3d& Vector3d::operator = (const Vector3d& vector)
{
	if (this == &vector)
		return *this;
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	return *this;
}


void Vector3d::setCoordinates(const double x, const double y, const double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3d::setVector(const Vector3d& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

double Vector3d::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3d::normalize()
{
	const double length = magnitude();
	x /= length;
	y /= length;
	z /= length;
}

Vector3d Vector3d::normal() const
{
	const double length = magnitude();
	return Vector3d(x/ length, y / length, z / length);
}

Vector3d& Vector3d::operator += (const Vector3d& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

Vector3d Vector3d::operator + (const Vector3d& vector)
{
	Vector3d res(x + vector.x, y + vector.y, z + vector.z);
	return res;
}

Vector3d Vector3d::operator * (double scale)
{
	Vector3d res(x*scale, y*scale, z*scale);
	return res;
}

double Vector3d::operator * (const Vector3d& vector)
{
	double res = x * vector.x + y * vector.y + z * vector.z;
	return res;
}


Vector3d& Vector3d::operator *= (double scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;

}

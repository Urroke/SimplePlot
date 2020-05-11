#include "../headers/Point3d.h"
Point3d::Point3d()
{
	x = y = z = 0;
}

Point3d::Point3d(const double x, const double y, const double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3d::Point3d(const Point3d& point)
{
	*this = point;
}

Vector3d Point3d::toVector() const
{
	return Vector3d(x, y, z);
}

Point3d& Point3d::operator = (const Point3d& point)
{
	if (this == &point)
		return *this;
	this->x = point.x;
	this->y = point.y;
	this->z = point.z;
	return *this;
}

void Point3d::setPoint(const double x, const double y, const double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3d operator - (const Point3d& point1, const Point3d& point2)
{
	return Vector3d(point1.x - point2.x, point1.y - point2.y, point1.z - point2.z);
}

Point3d operator + (const Point3d& point, const Vector3d& vector)
{
	return Point3d(point.x + vector.x, point.y + vector.y, point.z + vector.z);
}

Point3d operator - (const Point3d& point, const Vector3d& vector)
{
	return Point3d(point.x - vector.x, point.y - vector.y, point.z - vector.z);
}

Point3d& Point3d::operator+=(const Vector3d& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return *this;
}

Point3d& Point3d::operator-=(const Vector3d& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return *this;
}

Point3d& Point3d::operator*=(double scale)
{
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	return *this;
}


Point3d Point3d::getPoint() const
{
	return *this;
}
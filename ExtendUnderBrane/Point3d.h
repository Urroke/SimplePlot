#ifndef POINT3D_H
#define POINT3D_H
#include "Vector3d.h"

class Point3d
{
public:
	double x, y, z;

	Point3d();
	Point3d(double x, double y, double z);
	Point3d(const Point3d& point);

	Point3d& operator = (const Point3d& point);

	Vector3d toVector() const;
	void setPoint(double x, double y, double z);

	Point3d getPoint() const;

	const char* toStr();

	Point3d& operator+=(const Vector3d&);
	Point3d& operator-=(const Vector3d&);

	friend Vector3d operator - (const Point3d& point1, const Point3d& point2);
	friend Point3d operator + (const Point3d& point, const Vector3d& vector);
	friend Point3d operator - (const Point3d& point, const Vector3d& vector);
	~Point3d() = default;
};
#endif

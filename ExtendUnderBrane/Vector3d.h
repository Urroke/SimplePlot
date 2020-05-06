#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <math.h>

class Vector3d
{
public:
	double x, y, z;

	Vector3d();
	Vector3d(double x, double y, double z);
	Vector3d(const Vector3d& vector);

	Vector3d& operator = (const Vector3d& vector);
	Vector3d& operator += (const Vector3d& vector);
	Vector3d& operator *= (double);
	double operator * (const Vector3d& vector);
	Vector3d operator * (double);
	Vector3d operator + (const Vector3d& vector);

	void setCoord(double x, double y, double z);
	void setVector(const Vector3d& vector);
	Vector3d getVector() const;

	double magnitude() const;
	void normalize();
	Vector3d normal() const;

	~Vector3d() = default;
};
#endif

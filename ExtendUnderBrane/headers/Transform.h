#pragma once
#include "Point3d.h"
#include "Vector3d.h"
#include <array>

using Matrix = std::array<std::array<double, 3>, 3>;

struct Transform
{
	Point3d position;
	Matrix rotation;
	double scale;
	Vector3d directionAxis;
	Vector3d refAxis;

	Transform();
	Transform(const Point3d&, const Matrix&, double);
	void setScale(double);
	void scaleTo(double);
	void translateTo(const Vector3d&);
	void setPosition(const Point3d&);
	Matrix getRotation(double, const Vector3d&);
	void setRotation(double, const Vector3d&);
	void rotateBy(double, const Vector3d&);
	void rotateBy(const Vector3d&);
};

Vector3d operator*(const Matrix& matrix, const Vector3d& vec);

Point3d operator*(const Matrix& matrix, const Point3d& pnt);
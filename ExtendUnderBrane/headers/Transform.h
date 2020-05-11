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

	Transform();
	Transform(const Point3d&, const Matrix&, double);
	void setScale(double);
	void scaleTo(double);
	void translateTo(const Vector3d&);
	void setPosition(const Point3d&);
	void moveUp(double);
	void moveDown(double);

	Matrix getRotation(double, const Vector3d&);
	void setRotation(double, const Vector3d&);
	void rotateBy(double, const Vector3d&);
	void rotatePitch(double);
	void rotateYaw(double);
	void rotateRoll(double);

};

Vector3d operator*(const Matrix& matrix, const Vector3d& vec);

Point3d operator*(const Matrix& matrix, const Point3d& pnt);
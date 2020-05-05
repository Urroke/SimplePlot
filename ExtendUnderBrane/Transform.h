#pragma once
#include "Point3d.h"
#include "Vector3d.h"
#include <array>

using Matrix = std::array<std::array<double, 3>, 3>;

struct Transform
{
private:
public:
	Point3d position;
	Matrix rotation;
	double scale;
	Transform();
	Transform(const Point3d&, const Matrix&, double);
	void setScale(double);
	void scaleTo(double);
	void translateTo(const Vector3d&);
	void setPosition(const Point3d&);
	void setRotation(double, const Vector3d&);
};

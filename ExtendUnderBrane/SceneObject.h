#pragma once
#include "transform.h"
#include <GL/glut.h>

struct drawOption
{
	Vector3d color;
	double lineWidth;
	double pointRadius;
	double derivParam;
};

class SceneObject
{
private:
	Transform transform;
	Point3d lcsPoint(const Point3d&);
	Point3d globalPoint(const Point3d&);
public:
	int id;
	SceneObject();
	virtual void render(const drawOption&) const = 0;
	~SceneObject() = default;
};


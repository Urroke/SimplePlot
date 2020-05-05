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

protected:
	
public:
	Transform transform;
	virtual Point3d lcsPoint(const Point3d&) const;
	virtual Point3d globalPoint(const Point3d&) const;
	int id;
	SceneObject();
	virtual void render(const drawOption&) const = 0;
	~SceneObject() = default;
};


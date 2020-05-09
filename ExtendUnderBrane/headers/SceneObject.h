#pragma once
#include <GL/glut.h>
#include "Transform.h"

class SceneObject
{
private:

protected:
	
public:
	Transform transform;
	virtual Point3d lscPoint(const Point3d&) const;		
	virtual Point3d gscPoint(const Point3d&) const;
	int id;
	SceneObject();
	virtual void render() const = 0;
	virtual ~SceneObject() = default;
};


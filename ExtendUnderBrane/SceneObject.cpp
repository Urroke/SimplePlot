#include "SceneObject.h"

Point3d SceneObject::lcsPoint(const Point3d& point)
{
	Point3d res = point - transform.position.toVector();
	return res;
}

Point3d SceneObject::globalPoint(const Point3d& point)
{
	Point3d res = point + transform.position.toVector();
	return res;
}
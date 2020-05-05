#include "SceneObject.h"

Point3d SceneObject::lcsPoint(const Point3d& point) const
{
	Point3d res = point - transform.position.toVector();
	return res;
}

Point3d SceneObject::globalPoint(const Point3d& point) const
{
	Point3d res = point + transform.position.toVector();
	return res;
}

SceneObject::SceneObject()
{
	//Нормальный ключ воткнуть
	id = rand()%1000000;
	transform.rotation[0] = { 1., 0., 0. };
	transform.rotation[1] = { 0., 1., 0. };
	transform.rotation[2] = { 0., 0., 1. };
	
	transform.scale = 1;
}
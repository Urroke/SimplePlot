#include "Circle.h"



Circle::Circle()
{
	radius = 0.1;
}

Circle::Circle(double radius)
{
	this->radius = radius;
}


Circle::~Circle()
{
}

void Circle::collision(SolidBody* obj)
{
	Circle* _obj = (Circle*)(obj);
	Vector3d direction = _obj->transform.position - this->transform.position;
	double distance = (direction).magnitude();
	Vector3d perpDirection(1., 0, 0);
	if (distance > 0) {
		perpDirection.y = direction.y / direction.x;
		direction.normalize();	
		perpDirection.normalize();
	}
	else
	{
		perpDirection = direction;
	}
	Vector3d sumVelocity = _obj->velocity + this->velocity;
	double objProjection = direction * sumVelocity;
	double thisProjection = perpDirection * sumVelocity;
	
	direction *= (direction*_obj->velocity);
	
	
	direction *= objProjection;
	perpDirection *= -thisProjection;
	
	if(distance < _obj->radius + this->radius)
	{
		if (distance > 0)
		_obj->transform.position += direction.normal() * (_obj->radius + this->radius - distance + 0.000001);
		this->velocity = perpDirection;
		_obj->velocity = direction;
	}

}

void Circle::render(const drawOption&) const
{
	double step = 0.1;
	glPointSize(1.);
	glEnable(GL_POINT_SMOOTH);
	glColor3d(1, 0, 0);
	double x, y;
	int i = 0;
	for(double r = -3.142;r < 3.142;r += step, i++)
	{
		x = radius * std::cos(r);
		y = radius * std::sin(r);
		Point3d pnt(x, y, 0);
		pnt *= transform.scale;
		pnt = this->globalPoint(pnt);
		x = pnt.x;
		y = pnt.y;
		glBegin(GL_POINTS);
		glVertex3d(x, y, 0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3d(x, y, 0);
		if (i > 0)
			glVertex3d(x, y, 0);
		glEnd();
	}
}

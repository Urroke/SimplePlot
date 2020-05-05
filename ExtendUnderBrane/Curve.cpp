#include "Curve.h"


Curve::Curve()
{
	x = { 0, 0 };
}


Curve::~Curve()
{
}

Curve::Curve(const real_function& func, const interval& interv)
{
	function = func;
	x = interv;
}

void Curve::iterator(const real_function2_index& func, double step) const
{
	int i = 0;
	for (double r = x.x1; r < x.x2; r += step,i++)
		func(r, function(r), i);
}

void Curve::setInterval(const interval& intrv)
{
	x = intrv;
}

void Curve::setFunction(const real_function& func)
{
	function = func;
}

double Curve::operator()(double x) const
{
	return function(x);
}

void Curve::render(const drawOption&) const
{
	double step = 0.01;
	glPointSize(1.);
	glEnable(GL_POINT_SMOOTH);
	glColor3d(1, 0, 0);
	double x_p, y_p;
	iterator(
		[&](double x, double y, int i)->double {
			Point3d pnt(x, y, 0);
			pnt = this->lscPoint(pnt);
			pnt = transform.rotation*pnt;
			pnt = this->gscPoint(pnt);
			x = pnt.x;
			y = pnt.y;
			glBegin(GL_POINTS);
			glVertex3d(x, y, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3d(x, y, 0);
			if(i > 0)
				glVertex3d(x, y, 0);
			glEnd();
			return 0;
		}
	, step);
}
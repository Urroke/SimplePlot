#include "Curve.h"


Curve::Curve()
{
	interval = { 0, 0 };
	drawOptions = CurveDrawOption();
}


Curve::~Curve() = default;

Curve::Curve(const real_function& function, const Interval& interval)
{
	this->function = function;
	this->interval = interval;
	this->drawOptions = CurveDrawOption();
}

void Curve::iterator(const real_function2_index& func, const double step) const
{
	auto i = 0;
	for (auto r = interval.x1; r < interval.x2; r += step,i++)
		func(r, function(r), i);
}

void Curve::setInterval(const Interval& interval)
{
	this->interval = interval;
}

void Curve::setFunction(const real_function& func)
{
	function = func;
}

double Curve::operator()(const double x) const
{
	return function(x);
}

void Curve::render() const
{
	const double step = 0.01;
	glPointSize(1.);
	glEnable(GL_POINT_SMOOTH);
	glColor3d(1, 0, 0); // red
	double x_p, y_p;
	iterator(
		[&](double x, double y, const int i)->double {
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
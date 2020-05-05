#include "Curve.h"


Curve::Curve()
{
	x = { 0, 0 };
}


Curve::~Curve()
{
}

Curve::Curve(real_function func, interval interv)
{
	function = func;
	x = interv;
}

void Curve::iterator(real_function func, double step) const
{
	for (double r = x.x1; r < x.x2; r += step)
		func(function(r));
}

void Curve::setInterval(interval intrv)
{
	x = intrv;
}

void Curve::setFunction(real_function func)
{
	function = func;
}

double Curve::operator()(double x) const
{
	return function(x);
}

void Curve::render(const drawOption&) const
{

}
#pragma once
#include <functional>
#include "SceneObject.h"

using real_function = std::function<double(double)>;
using interval = 
struct {
	double x1;
	double x2;
};

class Curve : public SceneObject
{
private:
	real_function function;
	interval x;
public:
	Curve();

	Curve(real_function func, interval);

	void iterator(real_function func, double step) const;

	void setInterval(interval);

	void setFunction(real_function func);

	double operator()(double) const;

	~Curve();

	virtual void render(const drawOption&) const override;
};


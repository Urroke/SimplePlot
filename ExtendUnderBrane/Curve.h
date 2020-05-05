#pragma once
#include <functional>
#include "SceneObject.h"

using real_function = std::function<double(double)>;
using real_function2 = std::function<double(double, double)>;
using real_function2_index = std::function<double(double, double, int)>;
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

	Curve(const real_function& func, const interval&);

	void iterator(const real_function2_index& func, double step) const;

	void setInterval(const interval&);

	void setFunction(const real_function& func);

	double operator()(double) const;

	~Curve();

	virtual void render(const drawOption&) const override;
};


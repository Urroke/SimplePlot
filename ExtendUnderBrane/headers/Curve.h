#pragma once
#include <functional>
#include "SceneObject.h"

using real_function = std::function<double(double)>;
using real_function2 = std::function<double(double, double)>;
using real_function2_index = std::function<void(double, double, int)>;
using Interval = 
struct {
	double x1;
	double x2;
};

class Curve : public SceneObject
{
	real_function function;
	Interval interval;
public:
	Curve();
	Curve(const real_function& function, const Interval& interval);

	struct CurveDrawOption
	{
		Vector3d color;
		double lineWidth;
		double pointRadius;
		double derivedParam;

	} drawOptions;

	void iterator(const real_function2_index& func, double step) const;

	void setInterval(const Interval& interval);

	void setFunction(const real_function& func);

	double operator()(double) const;

	~Curve();

	void render() const override;
};


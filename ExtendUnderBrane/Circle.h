#pragma once
#include "SolidBody.h"
#include "headers/SceneObject.h"


class Circle: public SceneObject
{
private:
	
public:
	double radius;
	virtual void render() const override;
	Circle();
	Circle(double radius);
	~Circle();
};

class circle
{
};


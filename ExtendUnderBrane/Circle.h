#pragma once
#include "SolidBody.h"

class Circle: public SolidBody
{
private:
	
public:
	double radius;
	virtual void collision(SolidBody*) override;
	virtual void render(const drawOption&) const override;
	Circle();
	Circle(double radius);
	~Circle();
};


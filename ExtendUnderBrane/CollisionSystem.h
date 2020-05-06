#pragma once
#include "SolidBody.h"
#include <vector>

class CollisionSystem
{
private:
	std::vector<SolidBody*> bodys;
public:
	CollisionSystem& operator += (SolidBody&);
	CollisionSystem& operator -= (SolidBody&);
	void collision();
	CollisionSystem();
	~CollisionSystem();
};


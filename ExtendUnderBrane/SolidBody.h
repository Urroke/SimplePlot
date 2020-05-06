#pragma once
#include "Vector3d.h"
#include "SceneObject.h"

class SolidBody : public SceneObject
{
private:
public:
	Vector3d velocity;
	virtual void collision(SolidBody*) = 0;
	SolidBody();
	~SolidBody();
};


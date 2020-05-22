#pragma once
#include "headers/Vector3d.h"
#include "headers/SceneObject.h"

class SolidBody : public SceneObject
{
private:
public:
	Vector3d velocity;
	virtual void collision(SolidBody*) = 0;
	SolidBody();
	~SolidBody();
};


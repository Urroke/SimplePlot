#pragma once
#include "SceneObject.h"
#include <vector>

class Cube : public SceneObject
{
	
public:
	Cube() = default;

	void render() const override;
};


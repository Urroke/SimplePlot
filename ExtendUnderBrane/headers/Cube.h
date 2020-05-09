#pragma once
#include <vector>
#include "SceneObject.h"

class Cube : public SceneObject
{
	
public:
	Cube() = default;

	void render() const override;
};


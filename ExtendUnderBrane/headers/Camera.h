#pragma once
#include "../pch.h"
#include <vector>
#include <functional>

#include "EventVector.h"
#include "Transform.h"

class Camera
{
private:

	Camera();
	Camera(Camera const&); 
	Camera& operator= (Camera const&);

	void lookAt(const Point3d& position, const Point3d& target, const Vector3d& refAxis);

	static Camera instance;
public:
	static Camera& getInstance() {
		return instance;
	}

	Transform tfm;
	void rotateBy(const Vector3d& vec);
	void translateTo(const Vector3d& vec);
	void update();

	~Camera() = default;
};


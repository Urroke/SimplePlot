#pragma once
#include <vector>
#include "SceneObject.h"

class Scene
{
	std::vector<const SceneObject*> objects;
	drawOption option;
public:
	Scene() = default;
	~Scene() = default;
	//����������� ������ �� �����
	Scene& operator+=(const SceneObject&);
	//���������� ������ �� �����
	Scene& operator-=(const SceneObject&);
	void render();
};


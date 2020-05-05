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
	//Подписываем объект на сцену
	Scene& operator+=(const SceneObject&);
	//Отписываем объект от сцены
	Scene& operator-=(const SceneObject&);
	void render();
};


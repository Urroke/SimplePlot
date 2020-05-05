#pragma once
#include <vector>
#include "SceneObject.h"
#include <functional>

class Scene
{
	std::vector<const SceneObject*> objects;
	std::vector<const std::function<void(void)>*> callBacks;
	drawOption option;
public:
	Scene() = default;
	~Scene() = default;
	//Подписываем объект на сцену
	Scene& operator+=(const SceneObject&);
	//Отписываем объект от сцены
	Scene& operator-=(const SceneObject&);

	void subscribeCallBack(const std::function<void(void)>&);
	void render();
};


#pragma once
#include <vector>
#include "SceneObject.h"
#include <functional>

class Scene
{
	std::vector<const SceneObject*> objects;
	std::vector<const std::function<void()>*> callBacks;
public:
	Scene();
	~Scene();
	/*\
		Добавить объект на сцену
	*/
	Scene& operator+=(const SceneObject&);
	/*\
		Удалить объект со сцены
	*/
	Scene& operator-=(const SceneObject&);

	void subscribeCallBack(const std::function<void()>&);
	void render();
};


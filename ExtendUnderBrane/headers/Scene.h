#pragma once
#include <vector>
#include <functional>
#include "SceneObject.h"

class Scene
{
	
	std::vector<const SceneObject*> objects;
	std::function<void(void)> callBack;
	Scene();
	~Scene();

	Scene(const Scene& other);

	/*Scene(Scene&& other) noexcept
		: objects(std::move(other.objects)),
		  callBacks(std::move(other.callBacks))
	{
	}

	Scene& operator=(const Scene& other)
	{
		if (this == &other)
			return *this;
		objects = other.objects;
		callBacks = other.callBacks;
		return *this;
	}

	Scene& operator=(Scene&& other) noexcept
	{
		if (this == &other)
			return *this;
		objects = std::move(other.objects);
		callBacks = std::move(other.callBacks);
		return *this;
	}*/

	static Scene instance;
public:
	static Scene& getInstance();

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


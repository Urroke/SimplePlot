#include "../headers/Scene.h"

Scene::Scene() = default;

Scene::~Scene() = default;

Scene::Scene(const Scene & other) = default;

Scene& Scene::getInstance()
{
	return instance;
}

Scene& Scene::operator+=(const SceneObject& obj)
{
	objects.push_back(&obj);
	render();
	return *this;
}

Scene& Scene::operator-=(const SceneObject& obj)
{
	for (auto i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->id == obj.id)
		{
			for (int j = i; j < objects.size() - 1; ++j)
				objects[j] = objects[1 + j];
			render();
			return *this;
		}
	}
	return *this;
}
void Scene::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& object : objects)
	{
		object->render();
	}
	//for (auto& callBack : callBacks)
	//	(*callBack)();
	if(callBack)callBack();
}

void Scene::subscribeCallBack(const std::function<void(void)>& call)
{
	callBack = call;
}

#include "Scene.h"

Scene& Scene::operator+=(const SceneObject& obj)
{
	objects.push_back(&obj);
	render();
	return *this;
}

Scene& Scene::operator-=(const SceneObject& obj)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->id == obj.id)
		{
			for (int j = i; j < objects.size() - 1; ++j)
				objects[j] = objects[j + 1];
			render();
			return *this;
		}
	}
	return *this;
}
void Scene::render()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->render(option);
	}
}

#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::collision()
{
	for (int i = 0; i < bodys.size(); ++i)
		for (int j = i; j < bodys.size(); ++j)
			if(i != j)
		{
			bodys[i]->collision(bodys[j]);
		}
}

CollisionSystem& CollisionSystem::operator+=(SolidBody& obj)
{
	bodys.push_back(&obj);
	collision();
	return *this;
}

CollisionSystem& CollisionSystem::operator-=(SolidBody& obj)
{
	for (int i = 0; i < bodys.size(); ++i)
	{
		if (bodys[i]->id == obj.id)
		{
			for (int j = i; j < bodys.size() - 1; ++j)
				bodys[j] = bodys[j + 1];
			return *this;
		}
	}
	return *this;
}
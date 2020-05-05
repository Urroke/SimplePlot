#pragma once
#include "EventVector.h"
#include <stdio.h>
#include <vector>
#include <functional>
class Camera
{
	Camera();
	Camera(Camera const&); 
	Camera& operator= (Camera const&);  




	static Camera* instance;
public:
	static Camera* getInstance() {
		if (instance == nullptr) {
			instance = new Camera();
			
		}
		return instance;
	}


	


	
	


	~Camera();
};


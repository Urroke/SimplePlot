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
	EventVector<void(void)> onKeyPress;



	static Camera* instance;
public:
	static Camera* getInstance() {
		if (instance == nullptr) {
			instance = new Camera();
			instance->onKeyPress.subscribe([]() {
				printf("KEK");
				});
		}
		return instance;
	}

	/*
		Do not call this method explicitly. Used to gather user input from Glut.
		Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void keyboard_event(const unsigned char c, const int x, const int y) const{
		printf("%c %d %d", c, x, y);
		instance->onKeyPress.call();
	}
	/*
		Do not call this method explicitly. Used to gather user input from Glut.
		Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void mousewhell_event(const int button, const int dir, const int x, const int y) const {
		printf("%c %d %d", button, dir);
	}
	
	


	
	


	~Camera();
};


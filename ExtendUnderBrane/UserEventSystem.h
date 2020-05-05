#pragma once
#include "EventVector.h"

class UserEventSystem
{
	static UserEventSystem* instance;
	UserEventSystem() = default;
	~UserEventSystem() = default;
public:
	static UserEventSystem& getInstance() {
		if (instance == nullptr) {
			instance = new UserEventSystem();
		}
		return *instance;
	}
	EventVector<void(unsigned char, int, int)> onKeyPress;

	

	



	/*
	Do not call this method explicitly. Used to gather user input from Glut.
	Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
*/
	void keyboard_event(const unsigned char c, const int x, const int y) const {
		printf("%c %d %d", c, x, y);
		instance->onKeyPress.call(c,x,y);
	}
	/*
		Do not call this method explicitly. Used to gather user input from Glut.
		Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void mousewhell_event(const int button, const int dir, const int x, const int y) const {
		printf("%c %d %d", button, dir);
	}

};


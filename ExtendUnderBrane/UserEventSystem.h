#pragma once
#include "EventVector.h"

class UserEventSystem
{
	EventVector<void(void)> onKeyPress;
	static UserEventSystem instance;


public:

	

	/*
	Do not call this method explicitly. Used to gather user input from Glut.
	Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
*/
	void keyboard_event(const unsigned char c, const int x, const int y) const {
		printf("%c %d %d", c, x, y);
		//instance.onKeyPress.call();
	}
	/*
		Do not call this method explicitly. Used to gather user input from Glut.
		Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void mousewhell_event(const int button, const int dir, const int x, const int y) const {
		printf("%c %d %d", button, dir);
	}

};


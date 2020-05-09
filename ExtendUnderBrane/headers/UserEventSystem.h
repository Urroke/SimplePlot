#pragma once
#include "EventVector.h"

enum class MouseWheelDirection
{
	UP,
	DOWN
};

class UserEventSystem
{
	static UserEventSystem instance;
	UserEventSystem() = default;
	~UserEventSystem() = default;
public:
	static UserEventSystem& getInstance() {		
		return instance;
	}
	EventVector<void, unsigned char, int, int> onKeyPress;
	EventVector<void, unsigned char, int, int> onKeyUp;
	EventVector<void, MouseWheelDirection,int,int> onMouseWheel;

	/*
	Do not call this method explicitly. Used to gather user input from Glut.
	Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void keyboard_event(const unsigned char c, const int x, const int y) const {
		//printf("%c %d %d", c, x, y);
		instance.onKeyPress.call(c,x,y);
	}
	void keyboard_event_up(const unsigned char c, const int x, const int y) const {
		//printf("%c %d %d", c, x, y);
		instance.onKeyUp.call(c, x, y);
	}
	/*
		Do not call this method explicitly. Used to gather user input from Glut.
		Не вызывайте метод самостоятельно. Он собирает пользовательский ввод через Glut;
	*/
	void mousewhell_event(const int button, const int dir, const int x, const int y) const {
		
		if(button == 0 )
		{
			const auto direction = dir > 0 ? MouseWheelDirection::UP : MouseWheelDirection::DOWN;
			instance.onMouseWheel.call(direction, x, y);
		}
	}
};


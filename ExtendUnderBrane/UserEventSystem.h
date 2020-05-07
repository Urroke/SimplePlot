#pragma once
#include "EventVector.h"
#include <GL/freeglut.h>
#include <set>

enum class MouseWheelDirection
{
	UP,
	DOWN
};

using key = unsigned char;
class UserEventSystem
{
	static UserEventSystem instance;
	UserEventSystem() = default;
	~UserEventSystem() = default;


	static void keyboard_event(unsigned char c, int x, int y) {
		instance.onKeyPress.call(c, x, y);
	}
	static void mousewhell_event(int button, int dir, int x,  int y) {

		if (button == 0)
		{
			const auto direction = dir > 0 ? MouseWheelDirection::UP : MouseWheelDirection::DOWN;
			instance.onMouseWheel.call(direction, x, y);
		}
	}
	static void keyup_event(key c, int x, int y)
	{
		instance.onKeyUp.call(c, x, y);
	}
	static void mosemove_event(int x, int y)
	{
		instance.onMouseMove.call(x, y);
	}


	std::set<unsigned char> keysPressed;
	inline static bool initialized = false;
	
public:
	bool isKeyPressed(key c)
	{
		bool i = keysPressed.find(c) != keysPressed.end();
		return i;
	}
	
	static bool isInitialized()
	{
		return initialized;
	}
	static void initialize()
	{
		glutKeyboardFunc(keyboard_event);
		glutMouseWheelFunc(mousewhell_event);
		glutKeyboardUpFunc(keyup_event);
		glutMotionFunc(mosemove_event);
		glutPassiveMotionFunc(mosemove_event);		
		initialized = true;
	}
	static UserEventSystem& getInstance() {
		
		return instance;
	}
	EventVector<void, unsigned char, int, int> onKeyPress = { [&](unsigned char c, int x, int y) {keysPressed.insert(c); } };
	EventVector<void, unsigned char, int, int> onKeyUp{ [&](unsigned char c, int x, int y) {keysPressed.extract(c); } };
	EventVector<void, MouseWheelDirection,int,int> onMouseWheel;
	EventVector<void, int,int, int, int> onMouseDown;
	EventVector<void, int,int> onMouseMove;
};


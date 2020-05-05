#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#ifdef _WIN64
#define ptr __int64
#else
#define ptr __int32
#endif // 

template <typename FunctionTemplate>
class EventVector
{
	std::unordered_map<ptr,std::function<FunctionTemplate>> handlers;
	
public:

	ptr subscribe(std::function<FunctionTemplate>& function) {		
		handlers[(ptr)&function] = function;	
		return (ptr)&function;
	}
	void unsubcribe(ptr pointer) {	
		handlers.erase(pointer);
	}
	
	void call(unsigned char c, int x, int y) {
		for (auto it = handlers.begin(); it != handlers.end(); ++it) {
			it->second(c,x,y);
		}
	}
	


};


#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#ifdef _WIN64
#define ptr __int64
#else
#define ptr __int32
#endif // 



template <typename ReturnType, typename... Args>
class EventVector
{
	 typedef std::function<ReturnType(Args...)> EventFunction;
	std::unordered_map<ptr,EventFunction> handlers;
	
public:

	ptr subscribe(EventFunction& function) {		
		handlers[(ptr)&function] = function;	
		return (ptr)&function;
	}
	void unsubcribe(ptr pointer) {	
		handlers.erase(pointer);
	}
	void call(Args... args) {
		for (auto it = handlers.begin(); it != handlers.end(); ++it) {
			it->second(args...);
		}
	}	
};


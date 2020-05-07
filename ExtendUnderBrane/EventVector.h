#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#ifdef _WIN64
#define URAPOINTER __int64
#else
#define URAPOINTER __int32
#endif // 



template <typename ReturnType, typename... Args>
class EventVector
{
	 typedef std::function<ReturnType(Args...)> EventFunction;
	std::unordered_map<URAPOINTER,EventFunction> handlers;
	
public:
	EventVector() = default;
	~EventVector() = default;
	
	EventVector(std::initializer_list<EventFunction> list)
	{
		for(auto i = list.begin(); i != list.end(); ++i)
		{
			handlers[(URAPOINTER)i] = *i;
		}
	}
	URAPOINTER subscribe(EventFunction& function) {		
		handlers[(URAPOINTER)&function] = function;	
		return (URAPOINTER)&function;
	}
	void unsubcribe(URAPOINTER pointer) {	
		handlers.erase(pointer);
	}
	void call(Args... args) {
		for (auto it = handlers.begin(); it != handlers.end(); ++it) {
			it->second(args...);
		}
	}	
};


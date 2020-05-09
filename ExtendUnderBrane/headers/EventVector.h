#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#ifdef _WIN64
#define m_pointer __int64
#else
#define m_pointer __int32
#endif // 



template <typename ReturnType, typename... Args>
class EventVector
{
	 typedef std::function<ReturnType(Args...)> EventFunction;
	std::unordered_map<m_pointer,EventFunction> handlers;
	
public:

	m_pointer subscribe(const EventFunction& function) {		
		handlers[(m_pointer)&function] = function;	
		return (m_pointer)&function;
	}
	void unsubcribe(m_pointer pointer) {	
		handlers.erase(pointer);
	}
	void call(Args... args) {
		for (auto it = handlers.begin(); it != handlers.end(); ++it) {
			it->second(args...);
		}
	}	
};


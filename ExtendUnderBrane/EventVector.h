#pragma once
#include <vector>
#include <functional>
template <typename FunctionTemplate>
class EventVector
{
	std::vector<std::function<FunctionTemplate>> handlers;


public:

	void subscribe(std::function<FunctionTemplate>& function) {
		handlers.push_back(function);
	}
	void operator+=(std::function<FunctionTemplate>& function) {
		handlers.push_back(function);
		return *this;
	}
	
	void call() {
		if (handlers.size() != 0) {
			for (int i = 0; i < handlers.size(); i++) {
				handlers.at(i)();
			}
		}
	}


};


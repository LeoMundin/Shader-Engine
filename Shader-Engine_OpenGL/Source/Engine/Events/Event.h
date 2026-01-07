#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <list>
#include <functional>

class Event 
{

public:
	Event(){};
	~Event(){};

	void Invoke() {
		// Loop through all subscribers, calling their function
		for (auto& func : _subscribers) {
			func();
		}
	}

	/// <summary>
	/// Adds a function instance to this events, list of subscribers
	/// </summary>
	/// <param name="func"> A lambda with a class instance as its "capture clause" and the subscribing function as its "code" </param>
	void AddSubscriber(std::function<void()> func) {
		this->_subscribers.push_back(func);
	}

	bool HasSubscribers() {
		bool hasSubscribers = false;
		if (_subscribers.size() != 0) {
			hasSubscribers = true;
		}
		return hasSubscribers;
	}

private :

	std::list<std::function<void()>> _subscribers;

};

#endif

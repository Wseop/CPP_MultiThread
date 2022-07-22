#pragma once

#include <mutex>
#include <stack>

template<typename T>
class LockStack
{
public:
	LockStack() {}

public:
	void Push(T data) {
		std::lock_guard<std::mutex> lock(_mutex);
		_stack.push(data);
		// for WaitPop
		_condVar.notify_one();
	}
	bool TryPop(T& data) {
		std::lock_guard<std::mutex> lock(_mutex);

		if (_stack.empty())
			return false;

		data = _stack.top();
		_stack.pop();
		return true;
	}
	void WaitPop(T& data) {
		std::unique_lock<std::mutex> lock(_mutex);
		_condVar.wait(lock, [this]() {
			return _stack.empty() == false;
		});

		data = _stack.top();
		_stack.pop();
	}

private:
	std::mutex _mutex;
	std::stack<T> _stack;
	std::condition_variable _condVar;
};


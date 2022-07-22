#pragma once

#include <mutex>
#include <queue>

template<typename T>
class LockQueue
{
public:
	LockQueue() {}

public:
	void Push(T data) {
		std::lock_guard<std::mutex> lock(_mutex);
		_queue.push(data);
		// for WaitPop
		_condVar.notify_one();
	}
	bool TryPop(T& data) {
		std::lock_guard<std::mutex> lock(_mutex);

		if (_queue.empty())
			return false;

		data = _queue.front();
		_queue.pop();
		return true;
	}
	void WaitPop(T& data) {
		std::unique_lock<std::mutex> lock(_mutex);
		_condVar.wait(lock, [this]() {
			return _queue.empty() == false;
		});

		data = _queue.front();
		_queue.pop();
	}

private:
	std::mutex _mutex;
	std::queue<T> _queue;
	std::condition_variable _condVar;
};

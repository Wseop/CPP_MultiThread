#include "ThreadManager.h"
#include "CoreTLS.h"
#include <atomic>

using namespace std;

ThreadManager::ThreadManager()
{
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(std::function<void(void)> callback)
{
	lock_guard<mutex> lock(_mutex);

	_threads.push_back(thread([=]() 
		{
			InitTLS();
			callback();
			DestroyTLS();
		}));
}

void ThreadManager::Join()
{
	for (thread& t : _threads) {
		if (t.joinable())
			t.join();
	}
	_threads.clear();
}

void ThreadManager::InitTLS()
{
	static atomic<int> threadId = 1;
	LThreadId = threadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{
}

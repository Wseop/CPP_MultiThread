#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include "TLS.h"
#include "RWSpinLock.h"

using namespace std;

RWSpinLock lock;
queue<int32_t> q;
static atomic<uint16_t> SThreadId = 1;

void Push()
{
	LThreadId = SThreadId.fetch_add(1);
	while (true)
	{
		WriteLockGuard writeLockGuard(lock);
		q.push(4321);
	}
}

void Front()
{
	LThreadId = SThreadId.fetch_add(1);
	while (true)
	{
		ReadLockGuard readLockGuard(lock);
		if (q.empty())
			cout << -1 << endl;
		else
			cout << q.front() << endl;
	}
}

void Pop()
{
	LThreadId = SThreadId.fetch_add(1);
	while (true)
	{
		WriteLockGuard writeLockGuard(lock);
		if (q.empty() == false)
			q.pop();
	}
}

int main(void) 
{
	thread t1(Push);
	thread t2(Front);
	thread t3(Pop);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
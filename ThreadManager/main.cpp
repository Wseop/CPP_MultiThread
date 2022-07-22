#include <iostream>
#include "ThreadManager.h"
#include "CoreTLS.h"

using namespace std;

void ThreadFunc() 
{
	while (true) 
	{
		cout << "Hi I'm Thread : " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

// ThreadManager Test
// 10개의 thread를 생성해서 각자 자신의 LThreadId를 1초마다 출력
int main(void) 
{
	ThreadManager* threadManager = new ThreadManager();

	for (int i = 0; i < 10; i++) 
	{
		threadManager->Launch(ThreadFunc);
	}
	threadManager->Join();

	return 0;
}
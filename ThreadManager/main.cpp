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
// 10���� thread�� �����ؼ� ���� �ڽ��� LThreadId�� 1�ʸ��� ���
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
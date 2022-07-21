#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// �����صΰ� ������ thread function���� �����ٰ� ����
thread_local int LThreadId = 0;

void ThreadFunc(int threadId) {
	LThreadId = threadId;

	while (true) {
		cout << "I'm Thread " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

int main(void) {
	vector<thread> threads;

	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(ThreadFunc, i));
	}
	for (thread& t : threads) {
		t.join();
	}

	return 0;
}
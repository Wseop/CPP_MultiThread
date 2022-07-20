// Event 기법
// Producer - Consumer 컨셉
// Producer가 data를 push하면서 Signal
// Consumer는 Signal이 오면 깨어나서 pop -> 다시 대기
// Consumer thread의 CPU 점유율을 낮출 수 있음

#include <iostream>
#include <mutex>
#include <thread>
#include <Windows.h>
#include <queue>

using namespace std;

HANDLE handle;
mutex m;
queue<int> q;

// data를 넣고 10000ms초 sleep
void Producer() {
	while (true) {
		{
			lock_guard<mutex> lock(m);
			q.push(1234);
		}
		::SetEvent(handle);
		this_thread::sleep_for(10000ms);
	}
}

// data가 있으면 꺼내서 출력
void Consumer() {
	while (true) {
		::WaitForSingleObject(handle, INFINITE);

		lock_guard<mutex> lock(m);
		if (q.empty() == false) {
			int data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main(void) {
	handle = ::CreateEvent(NULL/*보안 속성*/, false, false, NULL);

	thread producer(Producer);
	thread consumer(Consumer);

	producer.join();
	consumer.join();

	::CloseHandle(handle);

	return 0;
}
// Event ���
// Producer - Consumer ����
// Producer�� data�� push�ϸ鼭 Signal
// Consumer�� Signal�� ���� ����� pop -> �ٽ� ���
// Consumer thread�� CPU �������� ���� �� ����

#include <iostream>
#include <mutex>
#include <thread>
#include <Windows.h>
#include <queue>

using namespace std;

HANDLE handle;
mutex m;
queue<int> q;

// data�� �ְ� 10000ms�� sleep
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

// data�� ������ ������ ���
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
	handle = ::CreateEvent(NULL/*���� �Ӽ�*/, false, false, NULL);

	thread producer(Producer);
	thread consumer(Consumer);

	producer.join();
	consumer.join();

	::CloseHandle(handle);

	return 0;
}
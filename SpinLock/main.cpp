// SpinLock 구현
// CAS (Compare and Swap) 활용 

#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

class SpinLock {
public:
	void lock() {
		bool expected = false;
		bool desired = true;

		// CAS
		while (_locked.compare_exchange_strong(expected, desired) == false) {
			// CAS 후 expected의 값이 _locked의 값으로 대체됨
			expected = false;

			// Sleep 방식 추가
			// this_thread::sleep_for(100ms);
			this_thread::yield();
		}
	}
	void unlock() {
		_locked.store(false);
	}

private:
	atomic<bool> _locked = false;
};

int sum = 0;
SpinLock lock;

void Add() {
	for (int i = 0; i < 1'000'000; i++) {
		lock.lock();
		sum++;
		lock.unlock();
	}
}

void Sub() {
	for (int i = 0; i < 1'000'000; i++) {
		lock.lock();
		sum--;
		lock.unlock();
	}
}

int main(void) {
	thread add(Add);
	thread sub(Sub);

	add.join();
	sub.join();

	cout << sum << endl;

	return 0;
}
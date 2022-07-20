#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

vector<int> v;
mutex m;

void Push() {
	for (int i = 0; i < 10000; i++) {
		v.push_back(i);
	}
}

void LPush() {
	for (int i = 0; i < 10000; i++) {
		// lock과 unlock은 반드시 pair로
		m.lock();
		v.push_back(i);
		m.unlock();
	}
}

// RAII 패턴 (Resource Acquisition Is Initialization)
// 생성과 동시에 Lock,
// 소멸과 동시에 Unlock,
template<typename T>
class LockGuard {
public:
	LockGuard(T& mutex) {
		_mutex = &mutex;
		_mutex->lock();
	}
	~LockGuard() {
		_mutex->unlock();
	}

private:
	T* _mutex;
};
void MyLockGuardPush() {
	for (int i = 0; i < 10000; i++) {
		LockGuard<mutex> lockGuard(m);
		v.push_back(i);
	}
}
// lock_guard와 unique_lock을 지원함
void LockGuardPush() {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lockGuard(m);
		v.push_back(i);
	}
}
void UniqueLockPush() {
	for (int i = 0; i < 10000; i++) {
		// unique_lock(w/ defer_lock) 사용시, lock 시점을 직접 설정 가능
		unique_lock<mutex> uniqueLock(m, defer_lock);
		uniqueLock.lock();
		v.push_back(i);
	}
}

int main(void) {
	// CRASH 발생
	{
		/*thread t1(Push);
		thread t2(Push);

		t1.join();
		t2.join();

		cout << v.size() << endl;*/
	}
	// Lock 사용
	{
		thread t1(LPush);
		thread t2(LPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// RAII 패턴 (Resource Acquisition Is Initialization)
	{
		thread t1(MyLockGuardPush);
		thread t2(MyLockGuardPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// lock_guard 사용
	{
		thread t1(LockGuardPush);
		thread t2(LockGuardPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// unique_lock 사용
	{
		thread t1(UniqueLockPush);
		thread t2(UniqueLockPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}

	return 0;
}
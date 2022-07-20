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
		// lock�� unlock�� �ݵ�� pair��
		m.lock();
		v.push_back(i);
		m.unlock();
	}
}

// RAII ���� (Resource Acquisition Is Initialization)
// ������ ���ÿ� Lock,
// �Ҹ�� ���ÿ� Unlock,
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
// lock_guard�� unique_lock�� ������
void LockGuardPush() {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lockGuard(m);
		v.push_back(i);
	}
}
void UniqueLockPush() {
	for (int i = 0; i < 10000; i++) {
		// unique_lock(w/ defer_lock) ����, lock ������ ���� ���� ����
		unique_lock<mutex> uniqueLock(m, defer_lock);
		uniqueLock.lock();
		v.push_back(i);
	}
}

int main(void) {
	// CRASH �߻�
	{
		/*thread t1(Push);
		thread t2(Push);

		t1.join();
		t2.join();

		cout << v.size() << endl;*/
	}
	// Lock ���
	{
		thread t1(LPush);
		thread t2(LPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// RAII ���� (Resource Acquisition Is Initialization)
	{
		thread t1(MyLockGuardPush);
		thread t2(MyLockGuardPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// lock_guard ���
	{
		thread t1(LockGuardPush);
		thread t2(LockGuardPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}
	// unique_lock ���
	{
		thread t1(UniqueLockPush);
		thread t2(UniqueLockPush);

		t1.join();
		t2.join();

		cout << v.size() << endl;
	}

	return 0;
}
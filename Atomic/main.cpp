#include <iostream>
#include <thread>
// Atomic : All or Nothing
#include <atomic>

using namespace std;

//int sum = 0;
atomic<int> sum = 0;

void Add() {
	for (int i = 0; i < 1'000'000; i++) {
		// sum++;
		
		// �Ϲ� ������ ����ص� ������ atomic�̶�� ���� ������ַ��� atomic �Լ��� ���
		// ���ÿ� ������ ��� ������ thread���� ������ ������ �ٸ� thread�� �����
		// ������ ��� ���� �̽� �߻��� �� ����
		sum.fetch_add(1);
	}
}

void Sub() {
	for (int i = 0; i < 1'000'000; i++) {
		// sum--;
		sum.fetch_sub(1);
	}
}

int main(void) {
	// single thread
	Add();
	Sub();
	cout << sum << endl;

	// multi thread
	thread t1(Add);
	thread t2(Sub);
	t1.join();
	t2.join();
	cout << sum << endl;

	return 0;
}
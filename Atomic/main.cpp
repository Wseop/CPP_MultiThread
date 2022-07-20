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
		
		// 일반 연산을 사용해도 되지만 atomic이라는 것을 명시해주려면 atomic 함수를 사용
		// 동시에 접근할 경우 선점한 thread에서 끝나기 전까지 다른 thread는 대기함
		// 남발할 경우 성능 이슈 발생할 수 있음
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
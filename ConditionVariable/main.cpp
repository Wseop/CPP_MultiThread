// Condition_Variable
// - Lock과 함께 사용
// - Event와 유사하지만 Event는 Kernel Level, Condition_Variable은 User Level

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;

mutex m;
condition_variable cv;
queue<int> q;

void Producer() {
	int num = 0;

	// 1) Lock 획득
	// 2) 공유 변수 수정
	// 3) Lock 해제
	// 4) Condition_Variable을 통해 다른 Thread에게 통지
	while (true) {
		{
			unique_lock<mutex> lock(m);
			q.push(num++);
		}
		cv.notify_one();
	}
}

void Consumer() {
	// 1) Lock 획득
	// 2) 조건 확인
	// 2-1) 조건을 만족하면 Wake up & 코드 진행
	// 2-2) 조건을 만족하지 않으면 Lock 해제 후 Wait
	while (true) {
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() { return q.empty() == false; });
		
		cout << "Size : " << q.size();
		int data = q.front();
		q.pop();
		cout << " Data : " << data << endl;
	}
}

int main(void) {
	thread producer(Producer);
	thread consumer(Consumer);

	producer.join();
	consumer.join();

	return 0;
}
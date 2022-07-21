// Condition_Variable
// - Lock�� �Բ� ���
// - Event�� ���������� Event�� Kernel Level, Condition_Variable�� User Level

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

	// 1) Lock ȹ��
	// 2) ���� ���� ����
	// 3) Lock ����
	// 4) Condition_Variable�� ���� �ٸ� Thread���� ����
	while (true) {
		{
			unique_lock<mutex> lock(m);
			q.push(num++);
		}
		cv.notify_one();
	}
}

void Consumer() {
	// 1) Lock ȹ��
	// 2) ���� Ȯ��
	// 2-1) ������ �����ϸ� Wake up & �ڵ� ����
	// 2-2) ������ �������� ������ Lock ���� �� Wait
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
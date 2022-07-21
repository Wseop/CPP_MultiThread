#include <iostream>
#include <thread>

using namespace std;

int x = 0;
int y = 0;
int r1 = 0;
int r2 = 0;

bool ready = false;

void Thread1() {
	while (ready == false);

	x = 1;
	r1 = y;
}

void Thread2() {
	while (ready == false);

	y = 1;
	r2 = x;
}

int main(void) {
	int64_t count = 0;

	while (true) {
		ready = false;
		count++;

		x = y = r1 = r2 = 0;

		thread t1(Thread1);
		thread t2(Thread2);

		// ����!
		ready = true;

		// ����!
		t1.join();
		t2.join();

		// �̰� �����Ѱ�? - ���ü�, �ڵ����ġ
		// <CPU Pipleline>
		// Fetch - Decode - Execute
		//         Fetch  - Decode  - Execute
		//                  Fetch   - Decode  - Execute
		// ...
		if (r1 == 0 && r2 == 0)
			break;
	}

	cout << count << endl;

	return 0;
}
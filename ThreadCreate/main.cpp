#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void HelloThread() {
	cout << "Hello Thread" << endl;
}
void ArgThread(int arg) {
	cout << "arg : " << arg << endl;
}

int main(void) {
	//////////////////////////////////////////////////////////////////////////////////////////
	thread t(HelloThread);

	cout << "Hello Main" << endl;
	cout << "hardware concurrency : " << t.hardware_concurrency() << endl;
	cout << "id : " << t.get_id() << endl;
	
	// thread 종료 대기
	if (t.joinable())
		t.join();
	//////////////////////////////////////////////////////////////////////////////////////////
	
	cout << endl;
	
	//////////////////////////////////////////////////////////////////////////////////////////
	vector<thread> threads;
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(ArgThread, i));
	}
	// wait threads;
	for (int i = 0; i < 10; i++) {
		if (threads[i].joinable())
			threads[i].join();
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}
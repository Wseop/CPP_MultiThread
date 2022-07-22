#include <iostream>
#include <thread>
#include "ConcurrentStack.h"
#include "ConcurrentQueue.h"

using namespace std;

LockStack<int> cst;
LockQueue<int> cq;

void StPush() {
	while (true) {
		cst.Push(1234);
	}
}
void StTryPop() {
	while (true) {
		int data;

		if (cst.TryPop(data)) {
			cout << "Stack TryPop : " << data << endl;
		}
	}
}
void StWaitPop() {
	while (true) {
		int data;

		cst.WaitPop(data);
		cout << "Stack WaitPop : " << data << endl;
	}
}
void QPush() {
	while (true) {
		cq.Push(4321);
	}
}
void QTryPop() {
	while (true) {
		int data;

		if (cq.TryPop(data)) {
			cout << "Queue TryPop : " << data << endl;
		}
	}
}
void QWaitPop() {
	while (true) {
		int data;

		cq.WaitPop(data);
		cout << "Queue WaitPop : " << data << endl;
	}
}

int main(void) {
	thread t1, t2, t3;

#if 0
	// stack test
	t1 = thread(StPush);
	t2 = thread(StTryPop);
	t3 = thread(StWaitPop);
#else
	// queue test
	t1 = thread(QPush);
	t2 = thread(QTryPop);
	t3 = thread(QWaitPop);
#endif // 1

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
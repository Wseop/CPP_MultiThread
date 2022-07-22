#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <functional>

class ThreadManager
{
public:
	// Main Thread 초기화 (TLS 등)
	ThreadManager();
	// Join 등
	~ThreadManager();

public:
	// w/ Lock
	// thread 생성 및 추가
	// 각 thread는 TLS 초기화 -> callback 함수 수행 -> TLS 해제 순으로 동작하도록 구현
	void Launch(std::function<void(void)> callback);
	// 모든 thread join
	// thread clear
	void Join();

	// LThreadId 할당
	// 1부터 증가
	static void InitTLS();
	// 동적할당 해제 등
	static void DestroyTLS();

private:
	std::mutex _mutex;
	std::vector<std::thread> _threads;
};


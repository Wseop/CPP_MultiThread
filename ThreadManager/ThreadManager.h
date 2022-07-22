#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <functional>

class ThreadManager
{
public:
	// Main Thread �ʱ�ȭ (TLS ��)
	ThreadManager();
	// Join ��
	~ThreadManager();

public:
	// w/ Lock
	// thread ���� �� �߰�
	// �� thread�� TLS �ʱ�ȭ -> callback �Լ� ���� -> TLS ���� ������ �����ϵ��� ����
	void Launch(std::function<void(void)> callback);
	// ��� thread join
	// thread clear
	void Join();

	// LThreadId �Ҵ�
	// 1���� ����
	static void InitTLS();
	// �����Ҵ� ���� ��
	static void DestroyTLS();

private:
	std::mutex _mutex;
	std::vector<std::thread> _threads;
};


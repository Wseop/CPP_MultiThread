#pragma once

#include <mutex>

class AccountManager
{
public:
	// Singleton Pattern
	static AccountManager* Instance() {
		static AccountManager instance;
		return &instance;
	}
	AccountManager* GetAccount();
	void Process();

private:
	std::mutex _mutex;
};


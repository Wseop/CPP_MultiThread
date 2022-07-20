#pragma once

#include <mutex>

class UserManager
{
public:
	// Singleton Pattern
	static UserManager* Instance() {
		static UserManager instance;
		return &instance;
	}
	UserManager* GetUser();
	void Process();

private:
	std::mutex _mutex;
};


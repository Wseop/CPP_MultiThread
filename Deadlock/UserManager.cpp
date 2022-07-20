#include "UserManager.h"
#include "AccountManager.h"

using namespace std;

UserManager* UserManager::GetUser()
{
	lock_guard<mutex> lock(_mutex);
	// process
	return nullptr;
}

void UserManager::Process()
{
	lock_guard<mutex> lock(_mutex);
	AccountManager::Instance()->GetAccount();
}

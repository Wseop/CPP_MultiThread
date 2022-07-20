#include "AccountManager.h"
#include "UserManager.h"

using namespace std;

AccountManager* AccountManager::GetAccount()
{
	lock_guard<mutex> lock(_mutex);
	// process
	return nullptr;
}

void AccountManager::Process()
{
	lock_guard<mutex> lock(_mutex);
	UserManager::Instance()->GetUser();
}

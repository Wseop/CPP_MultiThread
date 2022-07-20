#include <iostream>
#include "AccountManager.h"
#include "UserManager.h"

using namespace std;

void Account() {
	for (int i = 0; i < 1; i++) {
		AccountManager::Instance()->Process();
	}
}

void User() {
	for (int i = 0; i < 1; i++) {
		UserManager::Instance()->Process();
	}
}

// <AccountManager>		<UserManager>
// 
// [account lock]
//                      [user lock]
// [user lock]
//                      [account lock]*
// 
// ------------- deadlock -------------

int main(void) {
	thread account(Account);
	thread user(User);

	account.join();
	user.join();

	return 0;
}
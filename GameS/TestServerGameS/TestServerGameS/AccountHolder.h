#pragma once
#include <vector>

class Account;
using namespace std;

class AccountHolder{
	vector<Account*> accountList;
public:
	void AddAccount(Account&, const int&);
	const int GetClientCount() const;
	void Leave(const Account&);
};
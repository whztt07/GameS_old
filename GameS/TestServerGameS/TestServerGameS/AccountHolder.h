#pragma once
#include <vector>

class Account;
using namespace std;

class AccountHolder{
	vector<Account*> accountList;
public:
	void	AddAccount(Account &currentAccount, int newAccountId);
	int		GetClientCount() const;
	void	Leave(const Account &account);
};
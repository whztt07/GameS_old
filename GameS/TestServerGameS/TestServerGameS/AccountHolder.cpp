#include "stdafx.h"

#include <vector>

#include "Account.h"
#include "AccountHolder.h"

using namespace std;

void AccountHolder::AddAccount(Account &currentAccount, int newId){
	Account::EnterSection();
	for (int i = 0; i < accountList.size(); i++){
		if (accountList[i]->GetAccountId() == newId){

			accountList[i]->accountId = -1;
			accountList[i]->personId = -1;
			accountList[i]->info = "NeedExit";
			accountList.erase(accountList.begin() + i);

			break;
		}
	}
	currentAccount.accountId = newId;
	accountList.push_back(&currentAccount);
	Account::LeaveSection();
}
int AccountHolder::GetClientCount() const{
	Account::EnterSection();
	int size = accountList.size();
	Account::LeaveSection();
	return size;
}

void AccountHolder::Leave(const Account &account){
	Account::EnterSection();
	for (int i = 0; i < accountList.size(); i++){
		if (accountList[i]->GetAccountId() == account.GetAccountId()){
			accountList.erase(accountList.begin() + i);
			break;
		}
	}
	Account::LeaveSection();
}
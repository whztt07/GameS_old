#include "stdafx.h"

#include <vector>

#include "Account.h"
#include "AccountHolder.h"

using namespace std;

void AccountHolder::AddAccount(Account& acc, const int& num){
	Account::EnterSection();
	for (int i = 0; i < accountList.size(); i++){
		if (accountList[i]->GetAccNum() == num){
			accountList[i]->accNum = -1;
			accountList[i]->persNum = -1;
			accountList[i]->dopInfo = "NeedExit";
			accountList.erase(accountList.begin() + i);

			break;
		}
	}
	acc.accNum = num;
	accountList.push_back(&acc);
	Account::LeaveSection();
}
const int AccountHolder::GetClientCount() const{
	Account::EnterSection();
	int size = accountList.size();
	Account::LeaveSection();
	return size;
}

void AccountHolder::Leave(const Account& acc){
	Account::EnterSection();
	for (int i = 0; i < accountList.size(); i++){
		if (accountList[i]->GetAccNum() == acc.GetAccNum()){
			accountList.erase(accountList.begin() + i);
			break;
		}
	}
	Account::LeaveSection();
}
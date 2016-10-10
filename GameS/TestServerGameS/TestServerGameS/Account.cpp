#include "stdafx.h"

#include <string>
#include <vector>

#include "Account.h"

using namespace std;

CRITICAL_SECTION Account::accountSection;

Account::Account() : accountId(-1), personId(-1), info("None"), lastAnswer(), lastRequest(){}


void Account::Init(){
	InitializeCriticalSection(&accountSection);
}

Account Account::GetCopyAccount() const{
	EnterCriticalSection(&accountSection);
	Account account = Account(*this);
	LeaveCriticalSection(&accountSection);
	return account;
}

void Account::SetPersonId(int newPersonId){
	EnterCriticalSection(&accountSection);
	personId = newPersonId;
	LeaveCriticalSection(&accountSection);
}

void Account::SetInfo(const string &newInfo){
	EnterCriticalSection(&accountSection);
	info = newInfo;
	LeaveCriticalSection(&accountSection);
}

void Account::SetLastAnswer(const string &newLastAnswer){
	EnterCriticalSection(&accountSection);
	lastAnswer = newLastAnswer;
	LeaveCriticalSection(&accountSection);
}

void Account::SetLastRequest(const string &newLastRequest){
	EnterCriticalSection(&accountSection);
	lastRequest = newLastRequest;
	LeaveCriticalSection(&accountSection);
}

void Account::SetPersonIdList(const vector<int> &newPersonIdList){
	EnterCriticalSection(&accountSection);
	personIdList = newPersonIdList;
	LeaveCriticalSection(&accountSection);
}

const int& Account::GetAccountId() const{
	return accountId;
}

const int& Account::GetPersonId() const{
	return personId;
}

const string& Account::GetInfo() const{
	return info;
}

const string& Account::GetLastAnswer() const{
	return lastAnswer;
}

const string& Account::GetLastRequest() const{
	return lastRequest;
}


void Account::EnterSection(){
	EnterCriticalSection(&accountSection); 
}
void Account::LeaveSection(){
	LeaveCriticalSection(&accountSection);
}

const vector<int>& Account::GetPersonIdList() const{
	return personIdList;
}
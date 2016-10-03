#include "stdafx.h"

#include <string>
#include <vector>

#include "Account.h"

using namespace std;

CRITICAL_SECTION Account::accountSection;

Account::Account() : accNum(-1), persNum(-1), dopInfo("None"), lastAnswer(), lastRequest(){}


void Account::Init(){
	InitializeCriticalSection(&accountSection);
}

Account* Account::GetCopy() const{
	EnterCriticalSection(&accountSection);
	Account *a = new Account(*this);
	LeaveCriticalSection(&accountSection);
	return a;
}


void Account::SetAccNum(const int &_accNum){
	EnterCriticalSection(&accountSection);
	accNum = _accNum;
	LeaveCriticalSection(&accountSection);
}

void Account::SetPersNum(const int &_persNum){
	EnterCriticalSection(&accountSection);
	persNum = _persNum;
	LeaveCriticalSection(&accountSection);
}

void Account::SetDopInfo(const string &_dopInfo){
	EnterCriticalSection(&accountSection);
	dopInfo = _dopInfo;
	LeaveCriticalSection(&accountSection);
}

void Account::SetLastAnswer(const string &_lastAnswer){
	EnterCriticalSection(&accountSection);
	lastAnswer = _lastAnswer;
	LeaveCriticalSection(&accountSection);
}

void Account::SetLastRequest(const string &_lastRequest){
	EnterCriticalSection(&accountSection);
	lastRequest = _lastRequest;
	LeaveCriticalSection(&accountSection);
}

void Account::SetPersIdList(const vector<int> &_persIdList){
	EnterCriticalSection(&accountSection);
	persIdList = _persIdList;
	LeaveCriticalSection(&accountSection);
}

const int Account::GetAccNum() const{
	return accNum;
}

const int Account::GetPersNum() const{
	return persNum;
}

const string Account::GetDopInfo() const{
	return dopInfo;
}

const string Account::GetLastAnswer() const{
	return lastAnswer;
}

const string Account::GetLastRequest() const{
	return lastRequest;
}


void Account::EnterSection(){
	EnterCriticalSection(&accountSection); 
}
void Account::LeaveSection(){
	LeaveCriticalSection(&accountSection);
}

const vector<int>& Account::GetPersIdList() const{
	return persIdList;
}
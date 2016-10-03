#pragma once
#include <string>

using namespace std;

class Account{
	friend class AccountHolder;
	static CRITICAL_SECTION accountSection;
	
	int accNum;
	int persNum;
	string dopInfo, lastAnswer, lastRequest;
	vector<int> persIdList;
	static void EnterSection();
	static void LeaveSection();
public:
	static void Init();
	Account();
	void SetAccNum(const int&);
	void SetPersNum(const int&);

	void SetDopInfo(const string&);
	void SetLastAnswer(const string&);
	void SetLastRequest(const string&);

	void SetPersIdList(const vector<int>&);

	const int GetAccNum() const;
	const int GetPersNum() const;

	const string GetDopInfo() const;
	const string GetLastAnswer() const;
	const string GetLastRequest() const;

	const vector<int>& GetPersIdList() const;

	Account* GetCopy() const;
	
};
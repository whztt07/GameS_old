#pragma once
#include <string>

using namespace std;

class Account{
	friend class AccountHolder;

	static	CRITICAL_SECTION	accountSection;	
			int					accountId;
			int					personId;
			string				info;
			string				lastAnswer;
			string				lastRequest;
			vector<int>			personIdList;



	static	void	EnterSection();
	static	void	LeaveSection();

public:
	Account();

	static	void				Init();

			
			void				SetPersonId(int newPersonId);
			void				SetInfo(const string &newInfo);
			void				SetLastAnswer(const string &newLastAnswer);
			void				SetLastRequest(const string &newLastRequest);
			void				SetPersonIdList(const vector<int> &newPersonIdList);

			const int&			GetAccountId() const;
			const int&			GetPersonId() const;
			const string&		GetInfo() const;
			const string&		GetLastAnswer() const;
			const string&		GetLastRequest() const;
			const vector<int>&	GetPersonIdList() const;

			Account				GetCopyAccount() const;
	
};
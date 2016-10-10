#pragma once
#include <vector>

class Data;
class Person;

class PersonHolder{
	vector<Person*> personList;
	const int&		GetIndex(int personId) const;
public:
	void	AddPerson(const Person &newPerson, int type);
	string	ResolutionGamePers(const vector<int> &personIdList, int personId) const;
	void	Exit(int personId);
	string	NeedUPD(int personId);
	string	NeedUI_UPD(int personId);
	void	Command(const string &command, int personId, const Data &data, bool fast);
	Person&	GetPerson(int index) const;
	int		GetPersonCount() const;
};
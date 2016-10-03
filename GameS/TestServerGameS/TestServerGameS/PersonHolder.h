#pragma once
#include <vector>

class Data;
class Person;

class PersonHolder{
	vector<Person*> personList;
	const int& GetIndex(const int&);
public:
	void AddPerson(const Person&, int);
	string ResolutionGamePers(const vector<int> &vec, const int &id);
	void Exit(const int&);
	string NeedUPD(const int&);
	string NeedUI_UPD(const int&);
	void Command(string, const int&, const Data&, bool); 
};
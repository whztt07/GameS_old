#pragma once

#include <vector>

using namespace std;

#include "Person.h"

class BasePersonHolder{
	vector<Person> personList;
public:
	void Init(const vector<Person> &);
	const Person& GetPerson(const int&) const;
};
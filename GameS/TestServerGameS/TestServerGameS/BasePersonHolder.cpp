#include "stdafx.h"

#include <vector>

#include "Person.h"
#include "BasePersonHolder.h"

using namespace std;

void BasePersonHolder::Init(const vector<Person> &vec){
	personList = vec;
}

const Person& BasePersonHolder::GetPerson(const int&i) const{
	return personList[i];
}
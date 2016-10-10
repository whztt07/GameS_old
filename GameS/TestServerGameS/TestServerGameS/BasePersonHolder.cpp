#include "stdafx.h"

#include <vector>

#include "Person.h"
#include "BasePersonHolder.h"

using namespace std;

void BasePersonHolder::Init(const vector<Person> &vec){
	//pers.dropList.push_back(Drop(13, 50, 1, 5));
	//pers.pointDrop = PointsDrop(30, 10, 60, 30, 1, 5);
	personList = vec;
}

const Person& BasePersonHolder::GetPerson(const int&i) const{
	return personList[i];
}
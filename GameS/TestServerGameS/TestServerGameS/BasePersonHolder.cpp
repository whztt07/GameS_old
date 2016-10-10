#include "stdafx.h"

#include <vector>

#include "Person.h"
#include "BasePersonHolder.h"

using namespace std;

void BasePersonHolder::Init(const vector<Person> &newPersonList){
	//pers.dropList.push_back(Drop(13, 50, 1, 5));
	//pers.pointDrop = PointsDrop(30, 10, 60, 30, 1, 5);
	personList = newPersonList;
}

const Person& BasePersonHolder::GetPerson(int index) const{
	return personList[index];
}
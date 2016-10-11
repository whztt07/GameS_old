#include "stdafx.h"

#include <vector>
#include <string>
#include "Person.h"
#include "PersonHolder.h"
using namespace std;

void PersonHolder::AddPerson(const Person &newPerson, int personType){
	Person *ppers = new Person(newPerson);
	ppers->SetType(personType);
	personList.push_back(ppers);
}

string PersonHolder::ResolutionGamePers(const vector<int> &personIdList, int personId) const{
	string s = "";
	bool ok = true;
	int size = personIdList.size();
	for (int i = 0; i < size; i++){
		if (personIdList[i] != personId && GetIndex(personIdList[i]) > -1){
			s = "PersPlays";
			ok = false;
			break;
		}
	}
	if (ok){
		if (GetIndex(personId) == -1){
			s = "NewPers";
		}
		else{
			s = "PersExist";
		}
	}
	return s;
}

const int& PersonHolder::GetIndex(int personId) const{
	int size = personList.size();
	for (int i = 0; i < size; i++){
		if (personList[i]->GetPersonId() == personId){
			return i;
		}
	}
	return -1;
}

void PersonHolder::Exit(int personId){
	if (personId > -1){
		int j = GetIndex(personId);
		if (j > -1){
			personList[j]->SetActive(false);
		}
	}
}

string PersonHolder::NeedUPD(int personId){
	int index = GetIndex(personId);
	string s_UPD = personList[index]->GetUpdate();
	if (s_UPD == "NULL"){
		personList[index]->SetNeedUpdate(true);
	}
	personList[index]->SetUpdate("NULL");
	return s_UPD;
}

string PersonHolder::NeedUI_UPD(int personId){
	int index = GetIndex(personId);
	return personList[index]->GetUiUpdate();
}

void PersonHolder::Command(const string &command, int personId, const Data &data, bool fast){
	int index = GetIndex(personId);
	if (!fast){
		if (personList[index]->GetDoes()){
			personList[index]->SetWait(true);
			personList[index]->SetWaitingCommand(command);
			personList[index]->SetWaitingData(data);
		}
		else{
			personList[index]->SetData(data);
			personList[index]->SetCommand(command);
		}
	}
	else{
		personList[index]->SetFastCommand(command);
		personList[index]->SetFastData(data);
	}
}

Person&	PersonHolder::GetPerson(int index) const{
	return *personList[index];
}

int		PersonHolder::GetPersonCount() const{
	return personList.size();
}

void PersonHolder::UpdatePersonStats(){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		personList[i]->UpdateStats();
		personList[i]->UpdateWeight();
	}
}

void PersonHolder::UpdatePersonCommand(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateCommand();
		
	
}

void PersonHolder::UpdatePersonAnimation(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateAnimation();

}
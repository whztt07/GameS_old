#include "stdafx.h"

#include <vector>
#include <string>
#include "Person.h"
#include "PersonHolder.h"
using namespace std;

void PersonHolder::AddPerson(const Person &pers, int type){
	Person *ppers = new Person(pers);
	ppers->SetType(type);
	personList.push_back(ppers);
}

string PersonHolder::ResolutionGamePers(const vector<int> &vec, const int &id){
	string s = "";
	bool ok = true;
	for (int i = 0; i < vec.size(); i++){
		if (vec[i] != id && GetIndex(vec[i]) > -1){
			s = "PersPlays";
			ok = false;
			break;
		}
	}
	if (ok){
		if (GetIndex(id) == -1){
			s = "NewPers";
		}
		else{
			s = "PersExist";
		}
	}
	return s;
}

const int& PersonHolder::GetIndex(const int &num){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		if (personList[i]->GetPersonId() == num){
			return i;
		}
	}
	return -1;
}

void PersonHolder::Exit(const int &num){
	if (num > -1){
		int j = GetIndex(num);
		if (j > -1){
			personList[j]->SetActive(false);
		}
	}
}

string PersonHolder::NeedUPD(const int &id){
	int index = GetIndex(id);
	string s_UPD = personList[index]->GetUpdate();
	if (s_UPD == "NULL"){
		personList[index]->SetNeedUpdate(true);
	}
	personList[index]->SetUpdate("NULL");
	return s_UPD;
}

string PersonHolder::NeedUI_UPD(const int &id){
	int index = GetIndex(id);
	return personList[index]->GetUiUpdate();
}

void PersonHolder::Command(string command, const int &id, const Data &data, bool b){
	int index = GetIndex(id);
	if (b){
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
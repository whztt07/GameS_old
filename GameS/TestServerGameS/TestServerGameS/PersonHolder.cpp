#include "stdafx.h"

#include <vector>
#include <string>
#include "Person.h"
#include "PersonHolder.h"
#include "Global.h"
#include "BasePersonHolder.h"
using namespace std;



void PersonHolder::Init(DropItemHolder &dropItemHolder, BasePersonHolder &basePersonHolder){	
	this->dropItemHolder = &dropItemHolder;
	this->basePersonHolder = &basePersonHolder;
	npcNumber = -2;
}

Person* PersonHolder::AddBasePerson(int index){
	Person *ppers = new Person(basePersonHolder->GetPerson(index));
	ppers->SetPersonId(npcNumber--);
	ppers->SetType(2);
	personList.push_back(ppers);
	return ppers;
}

void PersonHolder::AddPerson(const Person &newPerson){
	Person *ppers = new Person(newPerson);
	ppers->SetType(1);
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

string PersonHolder::NeedUpdate(int personId){	
	return personList[GetIndex(personId)]->NeedUpdate();
}

string PersonHolder::NeedUiUpdate(int personId){
	int index = GetIndex(personId);
	return personList[index]->GetUiUpdate();
}

void PersonHolder::Command(const string &command, int personId, const Data &data, bool fast){
	personList[GetIndex(personId)]->Command(command, data, fast);
}

Person&	PersonHolder::GetPerson(int index){
	return *personList[index];
}

int PersonHolder::GetPersonCount() const{
	return personList.size();
}

void PersonHolder::UpdatePersonStats(){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		personList[i]->UpdateStats();
		personList[i]->UpdateWeight();
	}
}

void PersonHolder::UpdateDead(){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		if (personList[i]->IsDead()){
			if (personList[i]->IsFullDead()){
				if (personList[i]->GetType() == 2){
					personList[i]->SetDelete(true);
				}
				else{
					personList[i]->SetCorpseSave(false);
					personList[i]->SetResInPlace(false);
				}
			}
		}
	}

}
void PersonHolder::UpdatePersonCommand(){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		personList[i]->UpdateCommand();
		switch (personList[i]->GetStatus()){
		case r_attack:
			personList[i]->SetTargetPerson(*personList[GetIndex(personList[i]->GetTargetNumber())]);
		}
	}		
}

void PersonHolder::UpdatePersonAnimation(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateAnimation();

}

void PersonHolder::UpdatePersonRegeneration(float deltaTime){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateRegeneration(deltaTime);

}

void PersonHolder::UpdatePersonBattleStatus(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateBattleStatus();
}
void PersonHolder::UpdatePersonList(){

	for (int i = 0; i < personList.size(); i++){
		if (personList[i]->IsDelete()){
			personList.erase(personList.begin() + i);
			i--;
		}
		else if (!personList[i]->PersonActive() && !personList[i]->GetBattle()){
			personList[i]->SetDelete(true);
		}
	}
}
	


void PersonHolder::UpdateClientData(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
	if (personList[i]->StartClientUpdate()){
		Vector3 position = personList[i]->GetPosition();
		float visibleRange = personList[i]->GetVisibleRange();
		int number = 0;
		string curS = "";
		for (int j = 0; j < size; j++){
			if (i != j){
				string s = personList[j]->NeedClientUpdate(position, visibleRange);
				if (s != "NULL") {
					number++;
					curS += s;
				}
			}
		}
		curS = to_string(number) + "|" + curS + "0|";
		personList[i]->FinishClientUpdate(curS);
	}

}


void PersonHolder::UpdateAction(float deltaTime){
	int n = personList.size();
	for (int i = 0; i < n; i++){
		personList[i]->UpdateAction(deltaTime);
		
	}
}




bool PersonHolder::PersonLive(int personId) const{
	int index = GetIndex(personId);
	if (index == -1) return false;
	return personList[index]->GetLive();
}

void PersonHolder::UpdatePersonBuff(float deltaTime){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i]->UpdateBuff(deltaTime);
}
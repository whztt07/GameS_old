#include "stdafx.h"

#include <vector>
#include <string>
#include "Person.h"
#include "PersonHolder.h"
#include "Global.h"
using namespace std;

void PersonHolder::Init(GeoData &geoData, DropItemHolder &dropItemHolder){
	this->geoData = &geoData;
	this->dropItemHolder = &dropItemHolder;
}

void PersonHolder::AddPerson(const Person &newPerson, int personType){
	Person ppers(newPerson);
	ppers.SetType(personType);
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
		if (personList[i].GetPersonId() == personId){
			return i;
		}
	}
	return -1;
}

void PersonHolder::Exit(int personId){
	if (personId > -1){
		int j = GetIndex(personId);
		if (j > -1){
			personList[j].SetActive(false);
		}
	}
}

string PersonHolder::NeedUpdate(int personId){	
	return personList[GetIndex(personId)].NeedUpdate();
}

string PersonHolder::NeedUiUpdate(int personId){
	int index = GetIndex(personId);
	return personList[index].GetUiUpdate();
}

void PersonHolder::Command(const string &command, int personId, const Data &data, bool fast){
	personList[GetIndex(personId)].Command(command, data, fast);	
}

Person&	PersonHolder::GetPerson(int index){
	return personList[index];
}

int PersonHolder::GetPersonCount() const{
	return personList.size();
}

void PersonHolder::UpdatePersonStats(){
	int size = personList.size();
	for (int i = 0; i < size; i++){
		personList[i].UpdateStats();
		personList[i].UpdateWeight();
	}
}

void PersonHolder::UpdatePersonCommand(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i].UpdateCommand();
		
	
}

void PersonHolder::UpdatePersonAnimation(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i].UpdateAnimation();

}

void PersonHolder::UpdatePersonRegeneration(float deltaTime){
	int size = personList.size();
	for (int i = 0; i < size; i++)
		personList[i].UpdateRegeneration(deltaTime);

}


void PersonHolder::UpdatePersonList(){
	
	for (int i = 0; i < personList.size(); i++){
		if (!personList[i].PersonActive()){
			personList.erase(personList.begin() + i);
			i--;
		}		
	}
}

void PersonHolder::UpdateClientData(){
	int size = personList.size();
	for (int i = 0; i < size; i++)
	if (personList[i].StartClientUpdate()){
		Vector3 position = personList[i].GetPosition();
		float visibleRange = personList[i].GetVisibleRange();
		int number = 0;
		string curS = "";
		for (int j = 0; j < size; j++){
			if (i != j){
				string s = personList[j].NeedClientUpdate(position, visibleRange);
				if (s != "NULL") {
					number++;
					curS += s;
				}
			}
		}
		curS = to_string(number) + "|" + curS + "0|";
		personList[i].FinishClientUpdate(curS);
	}

}


void PersonHolder::UpdateAction(float deltaTime){
	int n = personList.size();
	for (int i = 0; i < n; i++){

		if (geoData->FallingPerson(deltaTime, personList[i])){
			Vector3 targPos;
			int itemIndex;
			switch (personList[i].GetStatus()){
			case r_move:
				if (personList[i].GetNeedPathUpdate()){
					geoData->NeedPersonPath(personList[i], personList[i].GetMovePosition());
					personList[i].SetNeedPathUpdate(false);
					personList[i].SetMoving(false);
				}
				else{
					geoData->MoveRotation(deltaTime, personList[i]);
				}
				break;
			case _move:
				personList[i].SetMoving(true);
				geoData->MovePerson(deltaTime, personList[i]);
				break;
				/*
				case r_attack:
				targPos = var->personList[GetIndex(var->personList[i].targetNumber)].position;
				if (Vector3::Distance(var->personList[i].position, targPos) <= var->personList[i].attackRange){
				GeoDvig::TargetRotation(deltaTime, i);
				}
				else{
				if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.5){
				GeoDvig::NeedPersonPath(i, targPos);
				var->personList[i].dvig = false;
				}
				GeoDvig::MoveRotation(deltaTime, i);
				}
				break;
				case move_attack:

				targPos = var->personList[GetIndex(var->personList[i].targetNumber)].position;
				if (Vector3::Distance(var->personList[i].position, targPos) <= var->personList[i].attackRange){
				var->personList[i].status = r_attack;
				}
				else{
				if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.5){
				GeoDvig::NeedPersonPath(i, targPos);
				var->personList[i].status = r_attack;
				}
				else{
				var->personList[i].dvig = true;
				GeoDvig::MovePerson(deltaTime, i);
				}
				}
				break;
				case attack:

				GeoDvig::TargetDoesRotation(deltaTime, i);
				Attack(i);
				break;
				case r_pickup:
				itemIndex = GetItemIndex(var->personList[i].pickupNumber);
				if (itemIndex == -1){
				var->personList[i].status = idle;
				}
				else{
				targPos = var->dropItemList[itemIndex].position;
				if (Vector3::Distance(var->personList[i].position, targPos) <= 0.2){
				GeoDvig::TargetItemRotation(deltaTime, i);
				}
				else{
				if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.2){
				GeoDvig::NeedPersonPath(i, targPos);
				var->personList[i].dvig = false;
				}
				GeoDvig::MoveRotation(deltaTime, i);
				}
				}
				break;
				case move_pickup:
				itemIndex = GetItemIndex(var->personList[i].pickupNumber);
				if (itemIndex == -1){
				var->personList[i].status = idle;
				}
				else{
				targPos = var->dropItemList[itemIndex].position;
				if (Vector3::Distance(var->personList[i].position, targPos) <= 0.2){
				var->personList[i].status = r_pickup;
				}
				else{
				var->personList[i].dvig = true;
				GeoDvig::MovePerson(deltaTime, i);
				}
				}
				break;
				case pickup:
				Pickup(i);
				break;
				case statsUp:

				StatsUP(i);
				break;
				case useItem:

				UseItem(i);
				break;*/
			}
		}
		else{
			switch (personList[i].GetStatus()){

			case _move:
				personList[i].SetStatus(r_move);
				break;
			case move_attack:
				personList[i].SetStatus(r_attack);
				break;
			case move_pickup:
				personList[i].SetStatus(r_pickup);
				break;
			default:
				personList[i].SetStatus(idle);
				break;
			}
		}
	}
}



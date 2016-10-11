#include "stdafx.h"
#include <process.h>
#include <time.h>

#include "WorkMSQL.h"
#include "WorkFile.h"
#include "PersonHolder.h"
#include "BasePersonHolder.h"
#include "BaseItemHolder.h"
#include "BaseSpellHolder.h"
#include "DropItemHolder.h"
#include "SpawnPointHolder.h"
#include "MSQL_init_data.h"
#include "GeoData.h"
#include "UpdateData.h"
#include "GameLogic.h"
#include "Spell.h"
#include "Data.h"
#include "Global.h"

GameLogic::GameLogic(const MSQL_init_data &msql_init_data) : geoData(WorkFile::ReadGeoData()){
	InitializeCriticalSection(&gameSection);

	WorkMSQL::Init(msql_init_data);

	baseSpellHolder.Init(WorkMSQL::GetBaseSpell());

	Spell::SetMasteryLvlList(baseSpellHolder.GetMasteryLvlArray());

	baseItemHolder.Init(WorkMSQL::GetBaseItem());

	Person::Init(baseItemHolder, baseSpellHolder);

	basePersonHolder.Init(WorkMSQL::GetBasePerson());

	vector<int> vec;
	vector<SpawnPoint> vec2;
	vec.push_back(1);

	vec2.push_back(SpawnPoint(Vector3(14, 0, 14), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(7, 0, 6), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(5, 0, 15), vec, 10000));

	spawnPointHolder.Init(vec2);
}

void GameLogic::UpdateClientData(){
	int size = personHolder.GetPersonCount();

	for (int i = 0; i < size; i++)
	if (personHolder.GetPerson(i).StartClientUpdate()){
		Vector3 position = personHolder.GetPerson(i).GetPosition();
		float visibleRange = personHolder.GetPerson(i).GetVisibleRange();
		int number = 0;
		string curS = "";
		for (int j = 0; j < size; j++){
			if (i != j){
				string s = personHolder.GetPerson(i).NeedClientUpdate(position, visibleRange);
				if (s != "NULL") { 
					number++; 
					curS += s;
				}
			}
		}
		curS = to_string(number) + "|" + curS + "0|";
		personHolder.GetPerson(i).FinishClientUpdate(curS);
	}

}


unsigned _stdcall GameLogic::RunUpdate(void* pvoid){
	GameLogic *game = (GameLogic*)pvoid;
	unsigned int mainLogicTime = clock();
	while (1) {
		
		if (clock() - mainLogicTime >= 20){			
			mainLogicTime = clock();
			EnterCriticalSection(&game->gameSection);

			game->personHolder.UpdatePersonCommand();
			game->personHolder.UpdatePersonStats();
			game->UpdateAction();
			game->personHolder.UpdatePersonAnimation();
			game->UpdateClientData();

			LeaveCriticalSection(&game->gameSection);

		}
		int sleepTime = 20 - clock() + mainLogicTime;
		if (sleepTime > 0)
			Sleep(sleepTime);
	}
	return 1;
}

UpdateData GameLogic::GetUpdateData(){
	EnterCriticalSection(&gameSection);
	UpdateData data = UpdateData();
	data.personCount = personHolder.GetPersonCount();
	data.spawnPointCount = spawnPointHolder.GetSpawnPointCount();
	LeaveCriticalSection(&gameSection);
	return data;
}

void GameLogic::RunThread(){
	_beginthreadex(NULL, NULL, GameLogic::RunUpdate, this, NULL, NULL);
}

const Person& GameLogic::GetBasePerson(int index){
	EnterCriticalSection(&gameSection);
	Person pers = Person(basePersonHolder.GetPerson(index));
	LeaveCriticalSection(&gameSection);
	return pers;
}


void GameLogic::AddPerson(const Person &newPerson, int personType){
	EnterCriticalSection(&gameSection);
	personHolder.AddPerson(newPerson, personType);
	LeaveCriticalSection(&gameSection);
}

string GameLogic::ResolutionGamePers(const vector<int> &personIdList, int personId){
	EnterCriticalSection(&gameSection);
	string s = personHolder.ResolutionGamePers(personIdList, personId);
	LeaveCriticalSection(&gameSection);
	return s;
}

string GameLogic::NeedUPD(int personId){
	EnterCriticalSection(&gameSection);
	string s_UPD = personHolder.NeedUPD(personId);
	LeaveCriticalSection(&gameSection);
	return s_UPD;

}

string GameLogic::NeedUI_UPD(int personId){
	EnterCriticalSection(&gameSection);
	string s_UPD = personHolder.NeedUI_UPD(personId);
	LeaveCriticalSection(&gameSection);
	return s_UPD;
}



void GameLogic::Command(const string &command, int personId, const Data &data, bool fast){
	EnterCriticalSection(&gameSection);
	personHolder.Command(command, personId, data, fast);
	LeaveCriticalSection(&gameSection);
}

void GameLogic::Exit(int personId){
	EnterCriticalSection(&gameSection);
	personHolder.Exit(personId);
	LeaveCriticalSection(&gameSection);
}



void GameLogic::UpdateAction(){
	static unsigned int lastUpdate = clock();
	int n = personHolder.GetPersonCount();
	float dsTime = (float)(clock() - lastUpdate) / 1000.0;
	lastUpdate = clock();

	float dlTime = 0;
	while (dsTime > 0){

		if (dsTime > 0.025){
			dlTime = 0.025;
			dsTime -= 0.025;
		}
		else{
			dlTime = dsTime;
			dsTime = 0;
		}
		for (int i = 0; i < n; i++){

			if (geoData.FallingPerson(dlTime, personHolder.GetPerson(i))){
				Vector3 targPos;
				int itemIndex;
				switch (personHolder.GetPerson(i).GetStatus()){
				case r_move:
					if (personHolder.GetPerson(i).GetNeedPathUpdate()){
						geoData.NeedPersonPath(personHolder.GetPerson(i), personHolder.GetPerson(i).GetMovePosition());
						personHolder.GetPerson(i).SetNeedPathUpdate(false);
						personHolder.GetPerson(i).SetMoving(false);
					}
					else{
						geoData.MoveRotation(dlTime, personHolder.GetPerson(i));
					}
					break;
				case _move:
					personHolder.GetPerson(i).SetMoving(true);
					geoData.MovePerson(dlTime, personHolder.GetPerson(i));
					break;
					/*
				case r_attack:
				targPos = var->personList[GetIndex(var->personList[i].targetNumber)].position;
				if (Vector3::Distance(var->personList[i].position, targPos) <= var->personList[i].attackRange){
				GeoDvig::TargetRotation(dlTime, i);
				}
				else{
				if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.5){
				GeoDvig::NeedPersonPath(i, targPos);
				var->personList[i].dvig = false;
				}
				GeoDvig::MoveRotation(dlTime, i);
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
				GeoDvig::MovePerson(dlTime, i);
				}
				}
				break;
				case attack:

				GeoDvig::TargetDoesRotation(dlTime, i);
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
				GeoDvig::TargetItemRotation(dlTime, i);
				}
				else{
				if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.2){
				GeoDvig::NeedPersonPath(i, targPos);
				var->personList[i].dvig = false;
				}
				GeoDvig::MoveRotation(dlTime, i);
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
				GeoDvig::MovePerson(dlTime, i);
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
				switch (personHolder.GetPerson(i).GetStatus()){

				case _move:
					personHolder.GetPerson(i).SetStatus(r_move);
					break;
				case move_attack:
					personHolder.GetPerson(i).SetStatus(r_attack);
					break;
				case move_pickup:
					personHolder.GetPerson(i).SetStatus(r_pickup);
					break;
				default:
					personHolder.GetPerson(i).SetStatus(idle);
					break;
				}
			}
		}
	}
}
		
/*

void UPDLogic::MainLogic(){
Mechanic::BuffUPD();

Mechanic::UPDPersonStats();

Mechanic::UPDPersonCommand();

Mechanic::UPDAction();

Mechanic::SpawnPointUPD();

Mechanic::DeadUPD();

Mechanic::BattleStatusUPD();

Mechanic::UPDPersonList();

Mechanic::UPDAnimation();

Mechanic::UPDGameClientsData();

}


void UPDLogic::RegenLogic(){
Mechanic::Regen();
}*/

/*
unsigned int  dTime = 0, mainLogicTime = clock(), regenLogic = clock(), AILogic = clock();
while (1){



	if (clock() - mainLogicTime >= 20){

		UPDLogic::MainLogic();
		mainLogicTime = clock();
	}
	if (clock() - AILogic >= 200){
		AI::AIUPD();
		AILogic = clock();
	}

	if (clock() - regenLogic >= 1000){

		UPDLogic::RegenLogic();
		regenLogic = clock();
	}
	int sleepTime = 20 - clock() + mainLogicTime;
	if (sleepTime > 0)
		Sleep(sleepTime);
}*/
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
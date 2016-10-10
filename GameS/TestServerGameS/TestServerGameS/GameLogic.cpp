#include "stdafx.h"
#include <process.h>

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

	Person::Init(baseItemHolder);

	basePersonHolder.Init(WorkMSQL::GetBasePerson());

	vector<int> vec;
	vector<SpawnPoint> vec2;
	vec.push_back(1);

	vec2.push_back(SpawnPoint(Vector3(14, 0, 14), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(7, 0, 6), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(5, 0, 15), vec, 10000));

	spawnPointHolder.Init(vec2);
}

void GameLogic::Update(){

}


unsigned _stdcall GameLogic::RunUpdate(void* pvoid){
	GameLogic *game = (GameLogic*)pvoid;
	while (1) game->Update();
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


void GameLogic::AddPerson(const Person &newPerson, int type){
	EnterCriticalSection(&gameSection);
	personHolder.AddPerson(newPerson, type);
	LeaveCriticalSection(&gameSection);
}

string GameLogic::ResolutionGamePers(const vector<int> &vec, int id){
	EnterCriticalSection(&gameSection);
	string s = personHolder.ResolutionGamePers(vec, id);
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



void GameLogic::Command(const string &s, int id, const Data &data, bool b){
	EnterCriticalSection(&gameSection);
	personHolder.Command(s, id, data, b);
	LeaveCriticalSection(&gameSection);
}

void GameLogic::Exit(int num){
	EnterCriticalSection(&gameSection);
	personHolder.Exit(num);
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
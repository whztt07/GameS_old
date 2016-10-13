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
#include "SpawnPoint.h"
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


	personHolder.Init(geoData, dropItemHolder);

	SpawnPoint::Init(personHolder, basePersonHolder);

	vector<int> vec;
	vector<SpawnPoint> vec2;
	vec.push_back(1);

	vec2.push_back(SpawnPoint(Vector3(14, 0, 14), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(7, 0, 6), vec, 10000));
	vec2.push_back(SpawnPoint(Vector3(5, 0, 15), vec, 10000));

	spawnPointHolder.Init(vec2);
}


unsigned _stdcall GameLogic::RunUpdate(void* pvoid){
	GameLogic *game = (GameLogic*)pvoid;
	unsigned int mainLogicTime = clock();
	unsigned int time;
	float deltaTime, dsTime;
	while (1) {
		time = clock();
		deltaTime = (time - mainLogicTime)/1000.0;
		if (deltaTime >= 0.02){							
			mainLogicTime = clock();			
			EnterCriticalSection(&game->gameSection);

			while (deltaTime > 0){
				if (deltaTime > 0.025){
					dsTime = 0.025;
					deltaTime -= 0.025;
				}
				else{
					dsTime = dsTime;
					deltaTime = 0;
				}
				game->personHolder.UpdatePersonCommand();
				game->personHolder.UpdatePersonBuff(dsTime);
				game->personHolder.UpdatePersonStats();
				game->personHolder.UpdateAction(dsTime);
				game->personHolder.UpdatePersonRegeneration(dsTime);
				//Mechanic::BattleStatusUPD();
			}

			game->spawnPointHolder.SpawnUpdate();
			//Mechanic::DeadUPD();

			game->personHolder.UpdatePersonList();
			game->personHolder.UpdatePersonAnimation();
			game->personHolder.UpdateClientData();

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

string GameLogic::NeedUpdate(int personId){
	EnterCriticalSection(&gameSection);
	string s_UPD = personHolder.NeedUpdate(personId);
	LeaveCriticalSection(&gameSection);
	return s_UPD;

}

string GameLogic::NeedUiUpdate(int personId){
	EnterCriticalSection(&gameSection);
	string s_UPD = personHolder.NeedUiUpdate(personId);
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



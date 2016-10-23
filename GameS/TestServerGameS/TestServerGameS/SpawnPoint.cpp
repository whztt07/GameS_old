#include "stdafx.h"

#include <vector>
#include <time.h>

#include "SpawnPoint.h"
#include "Global.h"
#include "BasePersonHolder.h"
#include "PersonHolder.h"
#include "Global.h"
#include "Person.h"

using namespace std;

PersonHolder *SpawnPoint::personHolder;


int Random(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

float Randomf(int min, int max){
	return (rand() % ((max - min) * 100 + 1)) / 100.0 + min;
}

SpawnPoint::SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime) : npcIdList(npcIdList), 
respawnTime(respawnTime), patrolRange(NPC_PATROL_RANGE), spawnRange(NPC_SPAWN_RANGE), spawnPosition(spawnPosition), currentPerson(NULL),
deadTime(0) {}

void SpawnPoint::Init(PersonHolder &personHolder){
	SpawnPoint::personHolder = &personHolder;
}


void SpawnPoint::SpawnUpdate(){
		if (currentPerson){
			if (currentPerson->IsDead()){
				currentPerson = NULL;
				deadTime = clock();
			}
		}
		else{
			if (clock() - deadTime >= respawnTime){
				int rand = Random(0, npcIdList.size() - 1);
				currentPerson = personHolder->AddBasePerson(npcIdList[rand]);
			
				float range = spawnRange;
				float offsetX = Randomf(-1 * range, range), offsetZ = Randomf(-1 * range, range);
				currentPerson->SetPosition(Vector3(spawnPosition.x + offsetX, spawnPosition.y, spawnPosition.z + offsetZ));
				
			}
		}
	
}
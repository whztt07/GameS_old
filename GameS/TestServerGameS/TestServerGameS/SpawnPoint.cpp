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
BasePersonHolder *SpawnPoint::basePersonHolder;
int	SpawnPoint::npcNumber = -2;


int Random(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

float Randomf(int min, int max){
	return (rand() % ((max - min) * 100 + 1)) / 100.0 + min;
}

SpawnPoint::SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime) : npcIdList(npcIdList), 
respawnTime(respawnTime), patrolRange(NPC_PATROL_RANGE), spawnRange(NPC_SPAWN_RANGE), spawnPosition(spawnPosition), currentNpcId(-1),
deadTime() {}

void SpawnPoint::Init(PersonHolder &personHolder, BasePersonHolder &basePersonHolder){
	SpawnPoint::personHolder = &personHolder;
	SpawnPoint::basePersonHolder = &basePersonHolder;
}


void SpawnPoint::SpawnUpdate(){
		if (currentNpcId != -1){
			if (!personHolder->PersonLive(currentNpcId)){
				currentNpcId = -1;
				deadTime = clock();
			}
		}
		else{
			if (clock() - deadTime >= respawnTime){
				int rand = Random(0, npcIdList.size() - 1);
				Person person = basePersonHolder->GetPerson(npcIdList[rand]);

				int num = npcNumber--;				
				person.SetPersonId(num);
				currentNpcId = num;
				float range = spawnRange;
				float offsetX = Randomf(-1 * range, range), offsetZ = Randomf(-1 * range, range);
				person.SetPosition(Vector3(spawnPosition.x + offsetX, spawnPosition.y, spawnPosition.z + offsetZ));
				personHolder->AddPerson(person, 2);
			}
		}
	
}
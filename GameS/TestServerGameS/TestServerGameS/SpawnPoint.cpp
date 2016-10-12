#include "stdafx.h"

#include <vector>

#include "SpawnPoint.h"
#include "Global.h"
#include "BasePersonHolder.h"
#include "PersonHolder.h"

using namespace std;

PersonHolder *SpawnPoint::personHolder;
BasePersonHolder *SpawnPoint::basePersonHolder;

SpawnPoint::SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime) : npcIdList(npcIdList), 
respawnTime(respawnTime), patrolRange(NPC_PATROL_RANGE), spawnRange(NPC_SPAWN_RANGE), spawnPosition(spawnPosition), currentNpcId(-1),
deadTime() {}

void SpawnPoint::Init(PersonHolder &personHolder, BasePersonHolder &basePersonHolder){
	SpawnPoint::personHolder = &personHolder;
	SpawnPoint::basePersonHolder = &basePersonHolder;
}
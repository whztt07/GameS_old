#include "stdafx.h"

#include <vector>

#include "SpawnPoint.h"
#include "Global.h"
using namespace std;

SpawnPoint::SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime) : npcIdList(npcIdList), 
respawnTime(respawnTime), patrolRange(NPC_PATROL_RANGE), spawnRange(NPC_SPAWN_RANGE), spawnPosition(spawnPosition), currentNpcId(-1),
deadTime() {}
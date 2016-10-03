#include "stdafx.h"

#include <vector>

#include "SpawnPoint.h"
#include "Global.h"
using namespace std;

SpawnPoint::SpawnPoint(const Vector3 &pos, const vector<int> &vec, const float& time) : idList(vec), respawnTime(time), patrolRange(NPC_PATROL_RANGE),
spawnRange(NPC_SPAWN_RANGE), spawnPosition(pos), curId(-1), deadTime() {}
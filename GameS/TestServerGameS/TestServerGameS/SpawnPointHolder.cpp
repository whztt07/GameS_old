#include "stdafx.h"

#include"SpawnPointHolder.h"

void SpawnPointHolder::Init(const vector<SpawnPoint> &newSpawnPointList){
	spawnPointList = newSpawnPointList;
}
int SpawnPointHolder::GetSpawnPointCount() const{
	return spawnPointList.size();
}
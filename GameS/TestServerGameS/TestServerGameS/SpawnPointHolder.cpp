#include "stdafx.h"

#include"SpawnPointHolder.h"

void SpawnPointHolder::Init(const vector<SpawnPoint> &newSpawnPointList){
	spawnPointList = newSpawnPointList;
}
int SpawnPointHolder::GetSpawnPointCount() const{
	return spawnPointList.size();
}

void SpawnPointHolder::SpawnUpdate(){
	int size = spawnPointList.size();

	for (int i = 0; i < size; i++)
		spawnPointList[i].SpawnUpdate();
}
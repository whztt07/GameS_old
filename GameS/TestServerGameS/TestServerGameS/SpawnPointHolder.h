#pragma once
#include <vector>

#include "SpawnPoint.h"
using namespace std;

class SpawnPointHolder{

	vector<SpawnPoint> spawnPointList;
public:
	void Init(const vector<SpawnPoint> &newSpawnPointList);

};
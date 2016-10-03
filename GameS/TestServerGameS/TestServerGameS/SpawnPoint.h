#pragma once
#include <vector>

#include "Vector3.h"

using namespace std;

class SpawnPoint {
	//индексы нпс которые могут заспавниться
	vector<int> idList;
	//Параметры
	float respawnTime, patrolRange, spawnRange;
	Vector3 spawnPosition;
	//id текущего нпс
	int curId;
	//Время когда освободилось место
	unsigned int deadTime;

public:
	SpawnPoint(const Vector3&, const vector<int>&, const float&);
		
};


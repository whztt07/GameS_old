#pragma once
#include <vector>

#include "Vector3.h"
#include "PersonHolder.h"

using namespace std;

class SpawnPoint {
	
			vector<int>			npcIdList;			//индексы нпс которые могут заспавниться	
			float				respawnTime;
			float				patrolRange;
			float				spawnRange;
			Vector3				spawnPosition;	
			Person		*currentPerson;		//id текущего нпс	
			unsigned int		deadTime;			//Время когда освободилось место
	static	PersonHolder		*personHolder;
public:	
	SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime);

	static	void	Init(PersonHolder &personHolder);

			void	SpawnUpdate();
};


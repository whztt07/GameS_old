#pragma once
#include <vector>

#include "Vector3.h"

using namespace std;

class SpawnPoint {
	
	vector<int>		npcIdList;		//������� ��� ������� ����� ������������	
	float			respawnTime;
	float			patrolRange;
	float			spawnRange;
	Vector3			spawnPosition;	
	int				currentNpcId;	//id �������� ���	
	unsigned int	deadTime;		//����� ����� ������������ �����

public:
	SpawnPoint(const Vector3 &spawnPosition, const vector<int> &npcIdList, float respawnTime);
};


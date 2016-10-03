#pragma once
#include <vector>

#include "Vector3.h"

using namespace std;

class SpawnPoint {
	//������� ��� ������� ����� ������������
	vector<int> idList;
	//���������
	float respawnTime, patrolRange, spawnRange;
	Vector3 spawnPosition;
	//id �������� ���
	int curId;
	//����� ����� ������������ �����
	unsigned int deadTime;

public:
	SpawnPoint(const Vector3&, const vector<int>&, const float&);
		
};


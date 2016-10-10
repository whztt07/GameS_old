#pragma once

#include <vector>

using namespace std;

#include "Mastery.h""

class MasteryHolder{
	
	vector<Mastery> masteryList;

public:
	
	MasteryHolder(int masteryCount);		//�������������� ������ �������� n ���������.

	const int&	GetMasteryCount() const;		
	Mastery&	GetMastery(int index);		//���������� Mastery ��� ������ � ���
};
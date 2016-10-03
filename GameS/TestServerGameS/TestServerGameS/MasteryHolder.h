#pragma once

#include <vector>

using namespace std;

#include "Mastery.h""

class MasteryHolder{
	
	vector<Mastery> masteryList;

public:
	//�������������� ������ �������� n ���������.
	MasteryHolder(const int&);
	const int& GetMasteryCount() const;
	//���������� Mastery ��� ������ � ���
	Mastery& GetMastery(const int&);
};
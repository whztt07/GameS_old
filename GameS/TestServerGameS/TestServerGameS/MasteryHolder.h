#pragma once

#include <vector>

using namespace std;

#include "Mastery.h""

class MasteryHolder{
	
	vector<Mastery> masteryList;

public:
	
	MasteryHolder(int masteryCount);		//Инициализирует массив создавая n элементов.

	const int&	GetMasteryCount() const;		
	Mastery&	GetMastery(int index);		//Возвращает Mastery для работы с ним
};
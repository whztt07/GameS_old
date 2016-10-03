#pragma once

#include <vector>

using namespace std;

#include "Mastery.h""

class MasteryHolder{
	
	vector<Mastery> masteryList;

public:
	//Инициализирует массив создавая n элементов.
	MasteryHolder(const int&);
	const int& GetMasteryCount() const;
	//Возвращает Mastery для работы с ним
	Mastery& GetMastery(const int&);
};
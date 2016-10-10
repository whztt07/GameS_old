#include "stdafx.h"
#include <vector>


#include "Mastery.h"
#include "MasteryHolder.h"

using namespace std;

MasteryHolder::MasteryHolder(int masteryCount){
	for (int i = 0; i < masteryCount; i++){
		masteryList.push_back(Mastery());
	}
}

Mastery& MasteryHolder::GetMastery(int index){
	return masteryList[index];
}

const int& MasteryHolder::GetMasteryCount() const{
	return masteryList.size();
}
#include "stdafx.h"
#include <vector>


#include "Mastery.h"
#include "MasteryHolder.h"

using namespace std;

MasteryHolder::MasteryHolder(const int& count){
	for (int i = 0; i < count; i++){
		masteryList.push_back(Mastery());
	}
}

Mastery& MasteryHolder::GetMastery(const int& i){
	return masteryList[i];
}

const int& MasteryHolder::GetMasteryCount() const{
	return masteryList.size();
}
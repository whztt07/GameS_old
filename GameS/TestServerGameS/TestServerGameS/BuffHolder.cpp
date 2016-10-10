#include "stdafx.h"

#include <vector>

#include "BuffHolder.h"

BuffHolder::BuffHolder(const int &buffCount){
	for (int i = 0; i < buffCount; i++){
		buffList.push_back(Buff());
	}
}

void BuffHolder::Init(const vector<Buff> &newBuffList){
	buffList = newBuffList;
}
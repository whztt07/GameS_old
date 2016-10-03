#include "stdafx.h"

#include <vector>

#include "BuffHolder.h"

BuffHolder::BuffHolder(const int &count){
	for (int i = 0; i < count; i++){
		buffList.push_back(Buff());
	}
}

void BuffHolder::Init(const vector<Buff> &vec){
	buffList = vec;
}
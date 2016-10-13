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

const Buff& BuffHolder::GetBuff(int index) const{
	return buffList[index];
}


void BuffHolder::AddBuff(int type, float time, int level){
	int freeSlot = -1, delSlot = -1;
	int size = buffList.size();
	for (int i = 0; i < size; i++){
		if (buffList[i].GetType() == -1 && freeSlot == -1){
			freeSlot = i;
		}
		if (buffList[i].GetType() != -1 && delSlot == -1 && !buffList[i].GetSpecial()){
			delSlot = i;
		}
		if (buffList[i].GetType() == type){
			if (buffList[i].GetLevel() <= level){
				buffList[i].SetLevel(level);
				buffList[i].SetTime(time);
				buffList[i].SetSpecial(false);				
			}
			return;
		}
	}
	if (freeSlot != -1){
		buffList[freeSlot].SetType(type);
		buffList[freeSlot].SetLevel(level);
		buffList[freeSlot].SetTime(time);
		buffList[freeSlot].SetSpecial(false);
		if (type >= 400){
			buffList[freeSlot].SetSpecial(true);
		}
	}
	else{
		if (delSlot != -1){
			buffList.erase(buffList.begin() + delSlot);
			buffList.push_back(Buff(type, level, time));	
			if (type >= 400){
				buffList.back().SetSpecial(true);
			}
		}
	}

}


void BuffHolder::DeleteBuff(int type){
	int size = buffList.size();
	for (int i = 0; i < size; i++){
		if (buffList[i].GetType() == type){
			buffList.erase(buffList.begin() + i);
			buffList.push_back(Buff());
		}
	}
}


void BuffHolder::UpdateBuffs(float deltaTime){
	int size = buffList.size();
	for (int j = 0; j < size; j++){
		if (!buffList[j].GetSpecial() && buffList[j].GetType() != -1){
			buffList[j].SubTime(deltaTime);
			if (buffList[j].GetTime() <= 0){
				DeleteBuff(buffList[j].GetType());
				j--;
				size--;
			}
		}
	}
}
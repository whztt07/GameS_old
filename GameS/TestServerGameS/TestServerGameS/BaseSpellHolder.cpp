

#include "stdafx.h"

#include <vector>

#include "SpellInfo.h"
#include "BaseSpellHolder.h"
#include "Global.h"

using namespace std;

void BaseSpellHolder::Init(const vector<SpellInfo> &vec){
	spellList = vec;
}

const SpellInfo& BaseSpellHolder::GetSpell(const int& i) const{
	return spellList[i];
}

const int* const BaseSpellHolder::GetMasteryLvlArray() const{
	int size = spellList.size();
	int *masteryLvl = new int[size];
	for (int i = 0; i < size; i++){
		masteryLvl[i] = -1;
		if (i > 19 && i < 26) masteryLvl[i] = 3;
		if (i > 25 && i < 32) masteryLvl[i] = 4;
		if (i > 31 && i < 38) masteryLvl[i] = 5;
		if (i > 37) masteryLvl[i] = 6;
	}
	return masteryLvl;
}


#include "stdafx.h"

#include <vector>

#include "Spell.h"
#include "SpellHolder.h"

using namespace std;

SpellHolder::SpellHolder(int spellCount){
	for (int i = 0; i < spellCount; i++){
		spellList.push_back(Spell(i));
	}
}

void SpellHolder::UpdateLvl(int masteryIndex, int masteryLvl){
	int size = spellList.size();
	for (int i = 0; i < size; i++){
		if (spellList[i].GetLvlType() == masteryIndex) spellList[i].SetLvl(masteryLvl);
	}
}

Spell& SpellHolder::GetSpell(int index){
	return spellList[index];
}
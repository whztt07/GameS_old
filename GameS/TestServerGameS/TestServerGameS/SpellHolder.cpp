#include "stdafx.h"

#include <vector>

#include "Spell.h"
#include "SpellHolder.h"

using namespace std;

SpellHolder::SpellHolder(const int &count){
	for (int i = 0; i < count; i++){
		spellList.push_back(Spell(i));
	}
}

void SpellHolder::UpdateLvl(const int &mastery, const int &lvl){
	int size = spellList.size();
	for (int i = 0; i < size; i++){
		if (spellList[i].GetLvlType() == mastery) spellList[i].SetLvl(lvl);
	}
}

Spell& SpellHolder::GetSpell(const int &i){
	return spellList[i];
}
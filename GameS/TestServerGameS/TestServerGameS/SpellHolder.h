#pragma once
#include <vector>

#include "Spell.h"

using namespace std;

class SpellHolder{
	vector<Spell> spellList;
public:
	SpellHolder(int spellCount);
	
	void	UpdateLvl(int masteryIndex, int masteryLvl);
	Spell&	GetSpell(int index);

};
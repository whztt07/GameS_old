#pragma once
#include <vector>

#include "Spell.h"

using namespace std;

class SpellHolder{
	vector<Spell> spellList;
public:
	SpellHolder(const int&);
	
	void UpdateLvl(const int&, const int&);

	Spell& GetSpell(const int&);

};
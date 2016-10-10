#pragma once
#include <vector>

#include "SpellInfo.h"

using namespace std;

class BaseSpellHolder{

	vector<SpellInfo> spellList;	
public:
	void				Init(const vector<SpellInfo> &newSpellInfoList);
	const SpellInfo&	GetSpell(int index) const;	
	const int* const	GetMasteryLvlArray() const;					//Возвращает информацию для инициализации Spell::lvlType
};
#pragma once
#include <vector>

#include "SpellInfo.h"

using namespace std;

class BaseSpellHolder{

	vector<SpellInfo> spellList;
	
public:
	void Init(const vector<SpellInfo>&);

	const SpellInfo& GetSpell(const int&) const;
	//Возвращает информацию для инициализации Spell::lvlType
	const int* const GetMasteryLvlArray() const;
};
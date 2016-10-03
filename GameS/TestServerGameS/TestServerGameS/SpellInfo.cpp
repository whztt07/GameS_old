#include "stdafx.h"

#include "SpellInfo.h"
#include "Global.h"

SpellInfo::SpellInfo() : masteryLvlNeed(new int[MASTERY_COUNT]){}

SpellInfo::SpellInfo(const SpellInfo &s) : active(s.active), learn(s.learn), range(s.range), castTime(s.castTime), cooldown(s.cooldown),
targetType(s.targetType), manaCost(s.manaCost), type(s.type), animType(animType), goldCost(s.goldCost), abilityPointCost(s.abilityPointCost),
spellPointCost(s.spellPointCost), intelligenceNeed(s.intelligenceNeed), masteryLvlNeed(new int[MASTERY_COUNT]){
	for (int i = 0; i < MASTERY_COUNT; i++)
		masteryLvlNeed[i] = s.masteryLvlNeed[0];
}

SpellInfo& SpellInfo::operator=(const SpellInfo &s){
	active = s.active;
	learn = s.learn;
	range = s.range;
	castTime = s.castTime;
	cooldown = s.cooldown;
	targetType = s.targetType;
	manaCost = s.manaCost;
	type = s.type;
	animType = animType;
	goldCost = s.goldCost;
	abilityPointCost = s.abilityPointCost;
	spellPointCost = s.spellPointCost;
	intelligenceNeed = s.intelligenceNeed;
	masteryLvlNeed = new int[MASTERY_COUNT];
	for (int i = 0; i < MASTERY_COUNT; i++)
		masteryLvlNeed[i] = s.masteryLvlNeed[0];

	return *this;
}

void SpellInfo::SetActive(const bool &_active){
	active = _active;
}

void SpellInfo::SetLearn(const bool &_learn){
	learn = _learn;
}

void SpellInfo::SetRange(const float &_range){
	range = _range;
}

void SpellInfo::SetCastTime(const float &_castTime){
	castTime = _castTime;
}

void SpellInfo::SetCooldown(const float &_cooldown){
	cooldown = _cooldown;
}


void SpellInfo::SetTargetType(const int &_targetType){
	targetType = _targetType;
}

void SpellInfo::SetManaCost(const int &_manaCost){
	manaCost = _manaCost;
}

void SpellInfo::SetType(const int &_type){
	type = _type;
}

void SpellInfo::SetAnimType(const int &_animType){
	animType = _animType;
}


void SpellInfo::SetGoldCost(const int &_goldCost){
	goldCost = _goldCost;
}

void SpellInfo::SetAbilityPointCost(const int &_abilityPointCost){
	abilityPointCost = _abilityPointCost;
}

void SpellInfo::SetSpellPointCost(const int &_spellPointCost){
	spellPointCost = _spellPointCost;
}

void SpellInfo::SetIntelligenceNeed(const int &_IntelligenceNeed){
	intelligenceNeed = _IntelligenceNeed;
}

void SpellInfo::SetMasteryLvlNeed(const int &i, const int &lvl){
	masteryLvlNeed[i] = lvl;
}


const int& SpellInfo::GetMasteryLvlNeed(const int &i) const{
	return masteryLvlNeed[i];
}


SpellInfo::~SpellInfo(){
	delete[] masteryLvlNeed;
}
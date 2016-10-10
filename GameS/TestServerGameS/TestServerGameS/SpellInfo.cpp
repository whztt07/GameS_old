#include "stdafx.h"

#include "SpellInfo.h"
#include "Global.h"

SpellInfo::SpellInfo() : masteryLvlNeed(new int[MASTERY_COUNT]){}

SpellInfo::SpellInfo(const SpellInfo &s) : active(s.active), learn(s.learn), range(s.range), castTime(s.castTime), cooldown(s.cooldown),
targetType(s.targetType), manaCost(s.manaCost), type(s.type), animationType(s.animationType), goldCost(s.goldCost), abilityPointCost(s.abilityPointCost),
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
	animationType = s.animationType;
	goldCost = s.goldCost;
	abilityPointCost = s.abilityPointCost;
	spellPointCost = s.spellPointCost;
	intelligenceNeed = s.intelligenceNeed;
	masteryLvlNeed = new int[MASTERY_COUNT];
	for (int i = 0; i < MASTERY_COUNT; i++)
		masteryLvlNeed[i] = s.masteryLvlNeed[0];

	return *this;
}

void SpellInfo::SetActive(bool newActive){
	active = newActive;
}

void SpellInfo::SetLearn(bool newLearn){
	learn = newLearn;
}

void SpellInfo::SetRange(float newRange){
	range = newRange;
}

void SpellInfo::SetCastTime(float newCastTime){
	castTime = newCastTime;
}

void SpellInfo::SetCooldown(float newCooldown){
	cooldown = newCooldown;
}


void SpellInfo::SetTargetType(int newTargetType){
	targetType = newTargetType;
}

void SpellInfo::SetManaCost(int newManaCost){
	manaCost = newManaCost;
}

void SpellInfo::SetType(int newType){
	type = newType;
}

void SpellInfo::SetAnimationType(int newAnimType){
	animationType = newAnimType;
}


void SpellInfo::SetGoldCost(int newGoldCost){
	goldCost = newGoldCost;
}

void SpellInfo::SetAbilityPointCost(int newAbilityPointCost){
	abilityPointCost = newAbilityPointCost;
}

void SpellInfo::SetSpellPointCost(int newSpellPointCost){
	spellPointCost = newSpellPointCost;
}

void SpellInfo::SetIntelligenceNeed(int newIntelligenceNeed){
	intelligenceNeed = newIntelligenceNeed;
}

void SpellInfo::SetMasteryLvlNeed(int masteryIndex, int newLvl){
	masteryLvlNeed[masteryIndex] = newLvl;
}


const int& SpellInfo::GetMasteryLvlNeed(int masteryIndex) const{
	return masteryLvlNeed[masteryIndex];
}


SpellInfo::~SpellInfo(){
	delete[] masteryLvlNeed;
}
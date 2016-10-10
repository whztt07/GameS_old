#include "stdafx.h"

#include "Spell.h"

const int *Spell::masteryLvl;

Spell::Spell(int spellNumber) : learn(), cooldown(), lvl(), lvlType(masteryLvl[spellNumber]){}

const float& Spell::GetCooldown() const{
	return cooldown;
}

const int& Spell::GetLvl() const{
	return lvl;
}

const int& Spell::GetLvlType() const{
	return lvlType;
}

void Spell::SetLearn(bool newLearn){
	learn = newLearn;
}

void Spell::SetCooldown(float newCooldown){
	cooldown = newCooldown;
}

void Spell::SetLvl(int newLvl){
	lvl = newLvl;
}

void Spell::SetMasteryLvlList(const int * const newList){
	masteryLvl = newList;
}
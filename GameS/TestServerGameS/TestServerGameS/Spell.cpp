#include "stdafx.h"

#include "Spell.h"

const int *Spell::masteryLvl;

Spell::Spell(const int& number) : learn(), cooldown(), lvl(), lvlType(masteryLvl[number]){}

const bool& Spell::GetLearn() const{
	return learn;
}

const float& Spell::GetCooldown() const{
	return cooldown;
}

const int& Spell::GetLvl() const{
	return lvl;
}

const int& Spell::GetLvlType() const{
	return lvlType;
}

void Spell::SetLearn(const bool& _learn){
	learn = _learn;
}

void Spell::SetCooldown(const float& _cooldown){
	cooldown = _cooldown;
}

void Spell::SetLvl(const int& _lvl){
	lvl = _lvl;
}

void Spell::SetMasteryLvlList(const int * const list){
	masteryLvl = list;
}
#include "stdafx.h"

#include "Mastery.h"
#include "Global.h"

const int *Mastery::lvlExpList = new int[MASTERY_MAX_LVL + 2]{MASTERY_EXP_ARRAY};

Mastery::Mastery() : lvl(), exp(), lvlUp() {}

void Mastery::SetLvl(int newLvl){
	int lvl = newLvl;
	if (lvl < 0) lvl = 0;
	if (lvl > MASTERY_MAX_LVL) lvl = MASTERY_MAX_LVL;
	lvl = lvl;
	exp = 0;
	lvlUp = true;
}

const int& Mastery::GetLvl() const{
	return lvl;
}

void Mastery::AddExp(float additionalExp){
	float exp = additionalExp;
	if (exp < 0) exp = 0;
	exp += exp;
	while (lvl < MASTERY_MAX_LVL){
		if (exp >= lvlExpList[lvl + 1]){
			exp -= lvlExpList[lvl + 1];
			lvl++;
			lvlUp = true;
		}
		else{
			break;
		}
	}
	if (lvl == MASTERY_MAX_LVL)
		exp = 0;	
}

const bool& Mastery::GetLvlUp() const{
	return lvlUp;
}
	

#include "stdafx.h"

#include "Mastery.h"
#include "Global.h"

const int *Mastery::lvlExpList = new int[MASTERY_MAX_LVL + 2]{MASTERY_EXP_ARRAY};

Mastery::Mastery() : curLvl(), curExp(), lvlUp() {}

void Mastery::SetLvl(const int &_lvl){
	int lvl = _lvl;
	if (lvl < 0) lvl = 0;
	if (lvl > MASTERY_MAX_LVL) lvl = MASTERY_MAX_LVL;
	curLvl = lvl;
	curExp = 0;
	lvlUp = true;
}

const int& Mastery::GetLvl() const{
	return curLvl;
}

void Mastery::AddExp(const float &_exp){
	float exp = _exp;
	if (exp < 0) exp = 0;
	curExp += exp;
	while (curLvl < MASTERY_MAX_LVL){
		if (curExp >= lvlExpList[curLvl + 1]){
			curExp -= lvlExpList[curLvl + 1];
			curLvl++;
			lvlUp = true;
		}
		else{
			break;
		}
	}
	if (curLvl == MASTERY_MAX_LVL)
		curExp = 0;	
}

const bool& Mastery::GetLvlUp() const{
	return lvlUp;
}
	

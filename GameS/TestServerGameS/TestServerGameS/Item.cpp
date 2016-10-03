#include "stdafx.h"

#include "Item.h"

void Item::SetType(const string &_type){
	type = _type;
}

void Item::SetSubType(const string &_subType){
	subType = _subType;
}

void Item::SetStack(const bool &_stack){
	stack = _stack;
}

void Item::SetWeight(const float &_weight){
	weight = _weight;
}

void Item::SetRangeAttack(const float &_rangeAttack){
	rangeAttack = _rangeAttack;
}

void Item::SetMinAttack(const int &_minAttack){
	minAttack = _minAttack;
}

void Item::SetMaxAttack(const int &_maxAttack){
	maxAttack = _maxAttack;
}

void Item::SetAccuracy(const int &_accuracy){
	accuracy = _accuracy;
}

void Item::SetAttackSpeed(const int &_attackSpeed){
	attackSpeed = _attackSpeed;
}

void Item::SetCritChance(const int &_critChance){
	critChance = _critChance;
}

void Item::SetCritRate(const int &_critRate){
	critRate = _critRate;
}

void Item::SetSpeedPenalty(const int &_speedPenalty){
	speedPenalty = _speedPenalty;
}

void Item::SetFailCastSpell(const int &_failCastSpell){
	failCastSpell = _failCastSpell;
}

void Item::SetResSlash(const int &_resSlash){
	resSlash = _resSlash;
}

void Item::SetResCrush(const int &_resCrush){
	resCrush = _resCrush;
}


void Item::SetResPierce(const int &_resPierce){
	resPierce = _resPierce;
}


void Item::SetEvasionPenalty(const int &_evasionPenalty){
	evasionPenalty = _evasionPenalty;
}


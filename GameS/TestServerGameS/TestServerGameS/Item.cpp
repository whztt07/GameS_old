#include "stdafx.h"

#include "Item.h"

void Item::SetType(const string &newType){
	type = newType;
}

void Item::SetSubType(const string &newSubType){
	subType = newSubType;
}

void Item::SetStack(bool newStack){
	stack = newStack;
}

void Item::SetWeight(float newWeight){
	weight = newWeight;
}

void Item::SetRangeAttack(float newRangeAttack){
	rangeAttack = newRangeAttack;
}

void Item::SetMinAttack(int newMinAttack){
	minAttack = newMinAttack;
}

void Item::SetMaxAttack(int newMaxAttack){
	maxAttack = newMaxAttack;
}

void Item::SetAccuracy(int newAccuracy){
	accuracy = newAccuracy;
}

void Item::SetAttackSpeed(int newAttackSpeed){
	attackSpeed = newAttackSpeed;
}

void Item::SetCritChance(int newCritChance){
	critChance = newCritChance;
}

void Item::SetCritRate(int newCritRate){
	critRate = newCritRate;
}

void Item::SetSpeedPenalty(int newSpeedPenalty){
	speedPenalty = newSpeedPenalty;
}

void Item::SetFailCastSpell(int newFailCastSpell){
	failCastSpell = newFailCastSpell;
}

void Item::SetResistSlash(int newResistSlash){
	resistSlash = newResistSlash;
}

void Item::SetResistCrush(int newResistCrush){
	resistCrush = newResistCrush;
}


void Item::SetResistPierce(int newResistPierce){
	resistPierce = newResistPierce;
}


void Item::SetEvasionPenalty(const int _evasionPenalty){
	evasionPenalty = _evasionPenalty;
}

const string& Item::GetType() const{
	return type;
}

const string& Item::GetSubType() const{
	return subType;
}

const bool& Item::GetStack() const{
	return stack;
}

const float& Item::GetWeight() const{
	return weight;
}

const float& Item::GetRangeAttack() const{
	return rangeAttack;
}

const int& Item::GetMinAttack() const{
	return minAttack;
}

const int& Item::GetMaxAttack() const{
	return maxAttack;
}

const int& Item::GetAccuracy() const{
	return accuracy;
}

const int& Item::GetAttackSpeed() const{
	return attackSpeed;
}

const int& Item::GetCritChance() const{
	return critChance;
}

const int& Item::GetCritRate() const{
	return critRate;
}

const int& Item::GetSpeedPenalty() const{
	return speedPenalty;
}

const int& Item::GetFailCastSpell() const{
	return failCastSpell;
}

const int& Item::GetResistSlash() const{
	return resistSlash;
}

const int& Item::GetResistCrush() const{
	return resistCrush;
}

const int& Item::GetResistPierce() const{
	return resistPierce;
}

const int& Item::GetEvasionPenalty() const{
	return evasionPenalty;
}

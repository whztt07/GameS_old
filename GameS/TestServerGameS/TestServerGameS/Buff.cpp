#include "stdafx.h"

#include "Buff.h"


Buff::Buff(int type, int level, float time, bool special) : type(type), level(level), time(time), special(special){}
Buff::Buff() : type(-1), level(1), time(), special(){}

const int& Buff::GetType() const{
	return type;
}

const int& Buff::GetLevel() const{
	return level;
}

void Buff::SetType(int newType){
	type = newType;
}

void Buff::SetLevel(int newLevel){
	level = newLevel;
}

void Buff::SetTime(float newTime){
	time = newTime;
}

void Buff::SetSpecial(bool newSpecial){
	special = newSpecial;
}

const float& Buff::GetTime() const{
	return time;
}

const bool&	Buff::GetSpecial() const{
	return special;
}


void Buff::SubTime(float deltaTime){
	time -= deltaTime;
}
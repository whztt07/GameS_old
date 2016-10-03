#pragma once
#include <string>

using namespace std;

class Item{
	//type {weapon, armor, other}, sub type {sword, blunt, bow}
	string type, subType;
	//���������� � 1 ����
	bool stack;
	//���������
	float weight, rangeAttack;
	//res - resist
	int minAttack, maxAttack, accuracy, attackSpeed, critChance, critRate, speedPenalty, failCastSpell, resSlash, resCrush,
		resPierce, evasionPenalty;
public:
	void SetType(const string&);
	void SetSubType(const string&);

	void SetStack(const bool&);

	void SetWeight(const float&);
	void SetRangeAttack(const float&);

	void SetMinAttack(const int&);
	void SetMaxAttack(const int&);
	void SetAccuracy(const int&);
	void SetAttackSpeed(const int&);
	void SetCritChance(const int&);
	void SetCritRate(const int&);
	void SetSpeedPenalty(const int&);
	void SetFailCastSpell(const int&);
	void SetResSlash(const int&);
	void SetResCrush(const int&);
	void SetResPierce(const int&);
	void SetEvasionPenalty(const int&);


};


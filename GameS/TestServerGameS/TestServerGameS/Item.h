#pragma once
#include <string>

using namespace std;

class Item{
	 
	string	type;			//type {weapon, armor, other}
	string	subType;		//sub type {sword, blunt, bow}	
	bool	stack;			//Складывать в 1 слот	
	float	weight;
	float	rangeAttack;	
	int		minAttack;
	int		maxAttack;
	int		accuracy;
	int		attackSpeed;
	int		critChance;
	int		critRate;
	int		speedPenalty;
	int		failCastSpell;
	int		resistSlash;
	int		resistCrush;
	int		resistPierce;
	int		evasionPenalty;
public:
	void			SetType(const string &newType);
	void			SetSubType(const string &newSubType);
	void			SetStack(bool newStack);
	void			SetWeight(float newWeight);
	void			SetRangeAttack(float newRangeAttack);
	void			SetMinAttack(int newMinAttack);
	void			SetMaxAttack(int newMaxAttack);
	void			SetAccuracy(int newAccuracy);
	void			SetAttackSpeed(int newAttackSpeed);
	void			SetCritChance(int newCritChance);
	void			SetCritRate(int newCritRate);
	void			SetSpeedPenalty(int  newSpeedPenalty);
	void			SetFailCastSpell(int  newFailSpellChance);
	void			SetResistSlash(int newResistSlash);
	void			SetResistCrush(int newResistCrush);
	void			SetResistPierce(int newResistPierce);
	void			SetEvasionPenalty(int newEvasionPenalty);

	const string&	GetType() const;
	const string&	GetSubType() const;
	const bool&		GetStack() const;
	const float&	GetWeight() const;
	const float&	GetRangeAttack() const;
	const int&		GetMinAttack() const;
	const int&		GetMaxAttack() const;
	const int&		GetAccuracy() const;
	const int&		GetAttackSpeed() const;
	const int&		GetCritChance() const;
	const int&		GetCritRate() const;
	const int&		GetSpeedPenalty() const;
	const int&		GetFailCastSpell() const;
	const int&		GetResistSlash() const;
	const int&		GetResistCrush() const;
	const int&		GetResistPierce() const;
	const int&		GetEvasionPenalty() const;
};


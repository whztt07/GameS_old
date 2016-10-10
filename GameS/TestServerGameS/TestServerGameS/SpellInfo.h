#pragma once


class SpellInfo{	
	bool	active;
	bool	learn;
	float	range;
	float	castTime;
	float	cooldown;
	int		targetType;
	int		manaCost;
	int		type;
	int		animationType;	
	int		goldCost;
	int		abilityPointCost;
	int		spellPointCost;
	int		intelligenceNeed;
	int		*masteryLvlNeed;
public:

	SpellInfo();
	SpellInfo(const SpellInfo&);
	~SpellInfo();

	SpellInfo&	operator=(const SpellInfo&);	
	
	void		SetActive(bool newActive);
	void		SetLearn(bool newLearn);
	void		SetRange(float newRange);
	void		SetCastTime(float newCastTime);
	void		SetCooldown(float newCooldown);
	void		SetTargetType(int newTargetType);
	void		SetManaCost(int newManaCost);
	void		SetType(int newType);
	void		SetAnimationType(int newAnimationType);
	void		SetGoldCost(int newGoldCost);
	void		SetAbilityPointCost(int newAbilityPointCost);
	void		SetSpellPointCost(int newSpellPointCost);
	void		SetIntelligenceNeed(int newIntelligenceNeed);
	void		SetMasteryLvlNeed(int masteryIndex, int newLvl);

	const int&	GetMasteryLvlNeed(int masteryIndex) const;
};	
#pragma once


class SpellInfo{

	//Параметры скила
	bool active, learn;
	float range, castTime, cooldown;
	int targetType, manaCost, type, animType;
	//Что нужно для изучения
	int goldCost, abilityPointCost, spellPointCost, intelligenceNeed;
	int *masteryLvlNeed;
public:

	SpellInfo();
	SpellInfo(const SpellInfo&);
	SpellInfo& operator=(const SpellInfo&);
	~SpellInfo();
	
	void SetActive(const bool&);
	void SetLearn(const bool&);

	void SetRange(const float&);
	void SetCastTime(const float&);
	void SetCooldown(const float&);

	void SetTargetType(const int&);
	void SetManaCost(const int&);
	void SetType(const int&);
	void SetAnimType(const int&);

	void SetGoldCost(const int&);
	void SetAbilityPointCost(const int&);
	void SetSpellPointCost(const int&);
	void SetIntelligenceNeed(const int&);
	void SetMasteryLvlNeed(const int&, const int&);


	const int& GetMasteryLvlNeed(const int&) const;
};	
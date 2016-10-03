#pragma once



class Spell{
	//Learn нужен для выборки изученных
	bool learn;
	float cooldown;
	//lvlType нужен, что бы показать от какого Mastery зависит уровень, если -1, то lvl всегда равен 1
	int lvl, lvlType;
	//Хранит информацию для инициализации lvlType
	static const int *masteryLvl;
public:
	//Инициализирует lvlType 
	Spell(const int&);	
	//Возвращает
	const bool& GetLearn() const;

	const float& GetCooldown() const;

	const int& GetLvl() const;
	const int& GetLvlType() const;
	//Устанавливает
	void SetLearn(const bool&);

	void SetCooldown(const float&);

	void SetLvl(const int&);

	static void SetMasteryLvlList(const int * const);
};
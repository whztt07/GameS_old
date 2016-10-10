#pragma once



class Spell{
	
			bool		learn;			//Learn нужен для выборки изученных
			float		cooldown;	
			int			lvl;
			int			lvlType;		//lvlType нужен, что бы показать от какого Mastery зависит уровень, если -1, то lvl всегда равен 1	
	static	const int	*masteryLvl;	//Хранит информацию для инициализации lvlType

public:
	 
	Spell(int spellNumber);	//Инициализирует lvlType

			
			const float&	GetCooldown() const;
			const int&		GetLvl() const;
			const int&		GetLvlType() const;
	
			void			SetLearn(bool newLearn);
			void			SetCooldown(float newCooldown);
			void			SetLvl(int newLvl);

	static	void			SetMasteryLvlList(const int * const newMasteryList);
};
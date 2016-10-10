#pragma once



class Spell{
	
			bool		learn;			//Learn ����� ��� ������� ���������
			float		cooldown;	
			int			lvl;
			int			lvlType;		//lvlType �����, ��� �� �������� �� ������ Mastery ������� �������, ���� -1, �� lvl ������ ����� 1	
	static	const int	*masteryLvl;	//������ ���������� ��� ������������� lvlType

public:
	 
	Spell(int spellNumber);	//�������������� lvlType

			
			const float&	GetCooldown() const;
			const int&		GetLvl() const;
			const int&		GetLvlType() const;
	
			void			SetLearn(bool newLearn);
			void			SetCooldown(float newCooldown);
			void			SetLvl(int newLvl);

	static	void			SetMasteryLvlList(const int * const newMasteryList);
};
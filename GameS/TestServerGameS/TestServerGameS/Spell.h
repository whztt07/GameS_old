#pragma once



class Spell{
	//Learn ����� ��� ������� ���������
	bool learn;
	float cooldown;
	//lvlType �����, ��� �� �������� �� ������ Mastery ������� �������, ���� -1, �� lvl ������ ����� 1
	int lvl, lvlType;
	//������ ���������� ��� ������������� lvlType
	static const int *masteryLvl;
public:
	//�������������� lvlType 
	Spell(const int&);	
	//����������
	const bool& GetLearn() const;

	const float& GetCooldown() const;

	const int& GetLvl() const;
	const int& GetLvlType() const;
	//�������������
	void SetLearn(const bool&);

	void SetCooldown(const float&);

	void SetLvl(const int&);

	static void SetMasteryLvlList(const int * const);
};
#pragma once

class Mastery{
	
	static	const int	*lvlExpList;	//������� ����� ����� ������� ��� ��������� ���������� ������. �������� lvlExp[4] = 30 ����������, ��� ��� ��������� � 3 �� 4 ������� ����� ������� ��� 30 �����
			int			lvl;
			float		exp;
			bool		lvlUp;
public:
	
	Mastery();
	
	void		SetLvl(int newLvl);		//������������� ������� � �������� �������� � ���������� ��������������� �-�� �����
	
	const int&	GetLvl() const;			//���������� �������
	const bool&	GetLvlUp() const;

	void		AddExp(float additionalExp);	//��������� ����, � ���� ����� �������� �������
};
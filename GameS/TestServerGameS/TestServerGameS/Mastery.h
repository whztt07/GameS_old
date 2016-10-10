#pragma once

class Mastery{
	
	static	const int	*lvlExpList;	//������� ����� ����� ������� ��� ��������� ���������� ������. �������� lvlExp[4] = 30 ����������, ��� ��� ��������� � 3 �� 4 ������� ����� ������� ��� 30 �����
			int			lvl;
			float		exp;
			bool		lvlUp;
public:
	
	Mastery();
	
			void			SetLvl(int newLvl);				//������������� ������� � �������� �������� � ���������� ��������������� �-�� �����
	
	static	const float&	GetLvlExp(int index);
			const float&	GetExp() const;
			const int&		GetLvl() const;					//���������� �������
			const bool&		GetLvlUp() const;

			void			AddExp(float additionalExp);	//��������� ����, � ���� ����� �������� �������
	
};
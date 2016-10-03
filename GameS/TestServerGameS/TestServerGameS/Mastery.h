#pragma once

class Mastery{
	//������� ����� ����� ������� ��� ��������� ���������� ������. �������� lvlExp[4] = 30 ����������, ��� ��� ��������� � 3 �� 4 ������� ����� ������� ��� 30 �����
	static const int *lvlExpList;
	int curLvl;
	float curExp;
	bool lvlUp;
public:
	
	Mastery();
	//������������� ������� � �������� �������� � ���������� ��������������� �-�� �����
	void SetLvl(const int&);
	//��������� ����, � ���� ����� �������� �������
	void AddExp(const float&);
	//���������� �������
	const int& GetLvl() const;
	const bool& GetLvlUp() const;
};
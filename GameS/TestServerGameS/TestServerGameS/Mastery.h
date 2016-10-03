#pragma once

class Mastery{
	//Сколько опыта нужно набрать для повышения следующего уровня. Например lvlExp[4] = 30 показывает, что для повышения с 3 на 4 уровень нужно набрать еще 30 опыта
	static const int *lvlExpList;
	int curLvl;
	float curExp;
	bool lvlUp;
public:
	
	Mastery();
	//Устанавливает уровень в указаное значенее и выставляет соответствующее к-во опыта
	void SetLvl(const int&);
	//Добавляет опыт, и если нужно повышает уровень
	void AddExp(const float&);
	//Возвращает уровень
	const int& GetLvl() const;
	const bool& GetLvlUp() const;
};
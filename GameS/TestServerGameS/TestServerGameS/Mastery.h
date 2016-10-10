#pragma once

class Mastery{
	
	static	const int	*lvlExpList;	//Сколько опыта нужно набрать для повышения следующего уровня. Например lvlExp[4] = 30 показывает, что для повышения с 3 на 4 уровень нужно набрать еще 30 опыта
			int			lvl;
			float		exp;
			bool		lvlUp;
public:
	
	Mastery();
	
	void		SetLvl(int newLvl);		//Устанавливает уровень в указаное значенее и выставляет соответствующее к-во опыта
	
	const int&	GetLvl() const;			//Возвращает уровень
	const bool&	GetLvlUp() const;

	void		AddExp(float additionalExp);	//Добавляет опыт, и если нужно повышает уровень
};
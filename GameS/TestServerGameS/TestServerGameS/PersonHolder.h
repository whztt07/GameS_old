#pragma once
#include <vector>

#include "GeoData.h"
#include "DropItemHolder.h"
#include "BasePersonHolder.h"
class Data;
class Person;

class PersonHolder{
	vector<Person*>		personList;
	DropItemHolder		*dropItemHolder;
	BasePersonHolder	*basePersonHolder;
	int					npcNumber;
	const int&	GetIndex(int personId) const;	
public:
	void	Init(DropItemHolder &dropItemHolder, BasePersonHolder &basePersonHolder);
	void	AddPerson(const Person &newPerson);
	string	ResolutionGamePers(const vector<int> &personIdList, int personId) const;
	void	Exit(int personId);
	string	NeedUpdate(int personId);
	string	NeedUiUpdate(int personId);
	void	Command(const string &command, int personId, const Data &data, bool fast);
	Person&	GetPerson(int index);
	int		GetPersonCount() const;
	void	UpdateClientData();
	void	UpdatePersonStats();
	void	UpdatePersonCommand();
	void	UpdatePersonRegeneration(float deltaTime);
	void	UpdatePersonAnimation();
	void	UpdatePersonList();
	void	UpdateAction(float deltaTime);
	void	UpdatePersonBuff(float deltaTime);
	void	UpdatePersonBattleStatus();
	void	UpdateDead();
	void	UpdatePersonAI();
	bool	PersonLive(int personId) const;
	Person* AddBasePerson(int index);
};
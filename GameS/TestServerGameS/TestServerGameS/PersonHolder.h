#pragma once
#include <vector>

#include "GeoData.h"
#include "DropItemHolder.h"
class Data;
class Person;

class PersonHolder{
	vector<Person>	personList;
	GeoData			*geoData;
	DropItemHolder	*dropItemHolder;

	const int& GetIndex(int personId) const;	
public:
	void	Init(GeoData &geoData, DropItemHolder &dropItemHolder);
	void	AddPerson(const Person &newPerson, int type);
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
};
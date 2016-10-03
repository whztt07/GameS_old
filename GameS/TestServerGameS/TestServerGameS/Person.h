#pragma once

#include <string>

using namespace std;

#include "Vector3.h";
#include "SpellHolder.h"
#include "MasteryHolder.h"
#include "BuffHolder.h"
#include "InventoryHolder.h"

class Person{
protected:
	//Имя персонажа
	string name;
	//Характеристики
	int race;
	int base_strength, base_agility, base_constitution, base_intelligence, base_wisdom, freeCharacteristics;
	int weaponSlot, bodySlot;
	float curHp, curMp, visibleRange;

	bool live, resInPlace;
	float corpseSaveTime;
	
	int persId, type;
	Vector3 position;
	float rotation;
	int characteristicPoint, abilityPoint, spellPoint;

	bool active;
	
public:
	SpellHolder spellList;
	MasteryHolder masteryList;
	BuffHolder buffList, debuffList;
	InventoryHolder inventory;

	Person();
			
	//Установка параметров
	void SetName(const string&);

	void SetRace(const int&);

	void SetBaseStrength(const int&);
	void SetBaseAgility(const int&);
	void SetBaseConstitution(const int&);
	void SetBaseIntelligence(const int&);
	void SetBaseWisdom(const int&);
	void SetFreeCharacteristics(const int&);

	void SetWeaponSlot(const int&);
	void SetBodySlot(const int&);

	void SetCurHp(const float&);
	void SetCurMp(const float&);
	void SetVisibleRange(const float&);
	

	void SetLive(const bool&);
	void SetResInPlace(const bool&);
	void SetCorpseSaveTime(const float&);

	void SetPersId(const int&);
	void SetType(const int&);

	void SetPosition(const Vector3&);
	void SetRotation(const float&);

	void SetCharacteristicPoint(const int&);
	void SetAbilityPoint(const int&);
	void SetSpellPoint(const int&);

	void SetActive(const bool&);
	//Получение параметров
	const string& GetName() const;

	const int& GetRace() const;

	const int& GetBaseStrength() const;
	const int& GetBaseAgility() const;
	const int& GetBaseConstitution() const;
	const int& GetBaseIntelligence() const;
	const int& GetBaseWisdom() const;
	const int& GetFreeCharacteristics() const;

	const int& GetWeaponSlot() const;
	const int& GetBodySlot() const;

	const float& GetCurHp() const;
	const float& GetCurMp() const;
	const float& GetVisibleRange() const;

	const bool& GetLive() const;
	const bool& GetResInPlace() const;
	const float& GetCorpseSaveTime() const;

	const int& GetPersId() const;
	const int& GetType() const;

	const Vector3& GetPosition() const;
	const float& GetRotation() const;

	const int& GetCharacteristicPoint() const;
	const int& GetAbilityPoint() const;
	const int& GetSpellPoint() const;

	void UpdateSpellLvl();
};
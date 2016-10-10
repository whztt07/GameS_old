#pragma once

#include <string>

using namespace std;

#include "Vector3.h";
#include "SpellHolder.h"
#include "MasteryHolder.h"
#include "BuffHolder.h"
#include "InventoryHolder.h"
#include "Data.h"
#include "BaseItemHolder.h"

class Person{
protected:
	
			string			name;		
			int				race;
			int				baseStrength;
			int				baseAgility;
			int				baseConstitution;
			int				baseIntelligence;
			int				baseWisdom;
			int				freeCharacteristics;
			int				weaponSlot;
			int				bodySlot;
			float			currentHp;
			float			currentMp;
			float			visibleRange;
			bool			live;
			bool			resInPlace;
			float			corpseSaveTime;	
			int				personId;
			int				type;
			Vector3			position;
			float			rotation;
			int				characteristicPoint;
			int				abilityPoint;
			int				spellPoint;
			bool			active;
			bool			needUpdate;
			bool			does;
			bool			wait;
			string			update;
			string			uiUpdate;
			string			waitingCommand;
			string			command;
			string			fastCommand;
			Data			data;
			Data			fastData;
			Data			waitingData;	
	static	BaseItemHolder	*baseItemHolder;

public:
	SpellHolder		spellList;
	MasteryHolder	masteryList;
	BuffHolder		buffList;
	BuffHolder		debuffList;
	InventoryHolder	inventory;
	
	Person();

	static	void			Init(BaseItemHolder &baseItemHolder);

			void			SetName(const string &newName);
			void			SetRace(int newRace);
			void			SetBaseStrength(int newBaseStrength);
			void			SetBaseAgility(int newBaseAgility);
			void			SetBaseConstitution(int newBaseConstitution);
			void			SetBaseIntelligence(int newBaseIntelligence);
			void			SetBaseWisdom(int newBaseWiasom);
			void			SetFreeCharacteristics(int newFreeCharacteristics);
			void			SetWeaponSlot(int newWeaponSlot);
			void			SetBodySlot(int newBodySlot);
			void			SetCurrentHp(float newCurrentHp);
			void			SetCurrentMp(float newCurrentMp);
			void			SetVisibleRange(float newVisibleRange);
			void			SetLive(bool newLive);
			void			SetResInPlace(bool newResInPlace);
			void			SetCorpseSaveTime(float newCorpseSaveTime);
			void			SetPersonId(int newPersonId);
			void			SetType(int newType);
			void			SetPosition(const Vector3 &newPosition);
			void			SetRotation(float newRotation);
			void			SetCharacteristicPoint(int newCharacteristicsPoint);
			void			SetAbilityPoint(int newAbilityPoint);
			void			SetSpellPoint(int newSpellPoint);
			void			SetActive(bool newActive);
			void			SetNeedUpdate(bool newNeedUpdate);
			void			SetUpdate(const string &newUpdate);
			void			SetWait(bool newWait);
			void			SetCommand(const string &newCommand);
			void			SetFastCommand(const string &newFastCommand);
			void			SetWaitingCommand(const string &newWaitingCommand);
			void			SetData(const Data &newData);
			void			SetFastData(const Data &newFastData);
			void			SetWaitingData(const Data &newWaitingData);

			const int&		GetPersonId() const;
			const string&	GetUpdate() const;
			const string&	GetUiUpdate() const;
			const bool&		GetDoes() const;
			const int&		GetRace() const;
			const float&	GetCurrentHp() const;
			const float&	GetCurrentMp() const;

			void			UpdateSpellLvl();
			void			UpdateStats();
};
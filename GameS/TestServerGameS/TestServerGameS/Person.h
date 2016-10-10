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
#include "BaseSpellHolder.h"

class Person{
protected:
	
			string			name;		
			int				race;
			int				baseStrength;
			int				baseAgility;
			int				baseConstitution;
			int				baseIntelligence;
			int				baseWisdom;
			int				strength;
			int				agility;
			int				constitution;
			int				intelligence;
			int				wisdom;
			int				modStrength;
			int				modAgility;
			int				modConstitution;
			int				modIntelligence;
			int				modWisdom;
			int				freeCharacteristics;
			int				weaponSlot;
			int				bodySlot;
			float			currentWeight;
			float			currentHp;
			float			currentMp;
			float			visibleRange;
			float			maxHp;
			float			maxMp;
			float			maxWeight;
			float			evasion;
			float			minAttack;
			float			maxAttack;
			float			attackSpeed;
			float			critChance;
			float			critRate;
			float			accuracy;
			float			speed;
			float			saveReaction;
			float			savePersistence;
			float			saveWill;
			float			saveDeath;
			float			complexitySpell;
			float			complexityAbility;
			float			invisible;
			float			detection;
			float			concentration;
			float			failSpellChance;
			float			rotationSpeed;
			float			attackRange;
			float			recoveryHp;
			float			recoveryMp;
			float			regenHpOutBattle;
			float			regenMpOutBattle;
			float			regenHpInBattle;
			float			regenMpInBattle;
			float			resistanceSlash;
			float			resistanceCrush;
			float			resistancePierce;
			float			resistanceFire;
			float			resistanceCold;
			float			resistanceNegative;
			bool			root;
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
			bool			needStatsUpdate;
			bool			does;
			bool			wait;
			bool			corpseSave;
			int				status;
			int				animationStatus;
			float			animationSpeed;
			int				targetNumber;
			string			update;
			string			uiUpdate;
			string			waitingCommand;
			string			command;
			string			fastCommand;
			Data			data;
			Data			fastData;
			Data			waitingData;	
	static	BaseItemHolder	*baseItemHolder;
	static	BaseSpellHolder	*baseSpellHolder;
public:
	SpellHolder		spellList;
	MasteryHolder	masteryList;
	BuffHolder		buffList;
	BuffHolder		debuffList;
	InventoryHolder	inventory;
	
	Person();

	static	void			Init(BaseItemHolder &baseItemHolder, BaseSpellHolder &baseSpellHolder);

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
			const Vector3&	GetPosition() const;
			const float&	GetVisibleRange() const;


			void			UpdateSpellLvl();
			void			UpdateStats();
			bool			StartClientUpdate();
			string			NeedClientUpdate(const Vector3 &personPosition, float visibleRange);
			void			FinishClientUpdate(const string &updateInfo);
};
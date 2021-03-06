#pragma once

#include <string>

using namespace std;

#include "Vector3.h";
#include "SpellHolder.h"
#include "MasteryHolder.h"
#include "BuffHolder.h"
#include "InventoryHolder.h"
#include "GeoData.h"
#include "Data.h"
#include "BaseItemHolder.h"
#include "BaseSpellHolder.h"

class Person{
protected:
	
			string			name;	
			string			update;
			string			uiUpdate;
			string			waitingCommand;
			string			command;
			string			fastCommand;
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
			int				personId;
			int				type;
			int				characteristicPoint;
			int				abilityPoint;
			int				spellPoint;
			int				status;
			int				animationStatus;
			int				targetNumber;
			int				useItemSlotNumber;
			int				pickupNumber;
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
			float			corpseSaveTime;	
			float			rotation;
			float			animationSpeed;
			float			attackTime;
			float			battleTime;
			bool			root;
			bool			live;
			bool			resInPlace;
			bool			active;
			bool			needUpdate;
			bool			needStatsUpdate;
			bool			needWeightUpdate;
			bool			does;
			bool			wait;
			bool			corpseSave;
			bool			needPathUpdate;
			bool			stand;
			bool			moving;
			bool			battle;
			bool			stan;
			bool			_delete;
			Data			data;
			Data			fastData;
			Data			waitingData;
			Data			statsUpData;			
			unsigned int	lastPersonUpdate;
			unsigned int	lastAttackTime;
			unsigned int	deadTime;
			Vector3			position;
			Vector3			movePosition;
			vector<Vector3>	pathList;
			Person			*targetPerson;
	static	BaseItemHolder	*baseItemHolder;
	static	BaseSpellHolder	*baseSpellHolder;
	static	GeoData			*geoData;
			
	void Attack();
public:
	SpellHolder		spellList;
	MasteryHolder	masteryList;
	BuffHolder		buffList;
	BuffHolder		debuffList;
	InventoryHolder	inventory;
	
	Person();

	static	void			Init(BaseItemHolder &baseItemHolder, BaseSpellHolder &baseSpellHolder, GeoData &geoData);

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
			void			SetStatus(int newStatus);
			void			SetStand(bool newStand);
			void			SetCorpseSave(bool newCorpseSave);
			void			SetPathList(const vector<Vector3> &newPathList);
			void			SetNeedPathUpdate(bool newNeedPathUpdate);
			void			SetMoving(bool newMoving);
			void			SetTargetPerson(Person &newTargetPerson);
			void			AddTargetPerson(Person &newTargetPerson);
			void			SetDelete(bool newDelete);
			const int&		GetPersonId() const;
			const string&	GetUiUpdate() const;
			const int&		GetRace() const;
			const float&	GetCurrentHp() const;
			const float&	GetCurrentMp() const;
			const Vector3&	GetPosition() const;
			const float&	GetVisibleRange() const;
			const bool&		GetRoot() const;
			const float&	GetSpeed() const;
			const int&		GetStatus() const;
			const Vector3&	GetMovePosition() const;
			const float&	GetRotation() const;
			const float&	GetRotationSpeed() const;
			const Vector3&	GetFirstPath() const;
			int				GetPathListSize() const;
			const bool&		GetNeedPathUpdate() const;
			const bool&		GetLive() const;
			const int&		GetTargetNumber() const;
			const Vector3&	GetLastPath() const;
			const float &	GetAttackRange() const;
			const bool&		GetBattle() const;
			const int&		GetType() const;
			const string&	GetCommand() const;

			void			Resurrection(bool place = false);
			void			UpdateAI();
			void			UpdateAction(float deltaTime);
			void			UpdateBattleStatus();
			void			UpdateSpellLvl();
			void			UpdateStats();
			void			UpdateWeight();
			void			UpdateCommand();
			void			UpdateBuff(float deltaTime);
			void			UpdateRegeneration(float deltaTime);
			void			UpdateAnimation();
			bool			StartClientUpdate();
			string			NeedClientUpdate(const Vector3 &personPosition, float visibleRange);
			void			FinishClientUpdate(const string &updateInfo);
			void			DeleteFirstPath();
			bool			PersonActive();
			const bool&		IsDead() const;
			bool			IsFullDead() const;
			const bool&		IsLive() const;
			const bool&		IsDelete() const;
			void			Kill(Person &killer);

			string			NeedUpdate();			
			void			Command(const string &command, const Data &data, bool fast);
			void			StatsUp();
			void			UseItem();
};
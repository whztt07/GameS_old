#pragma once
#include <string>
#include <vector>
#include <time.h>

#include "InventorySlot.h"
#include "Buff.h"
#include "Vector3.h"
#include "Enum.h"
#include "Drop.h"
#include "PointsDrop.h"
#include "Data.h"
#include "Mastery.h"
#include "Spell.h"
using namespace std;

#define INVENTORYSLOTCOUNT 20

class Person2 {
public:
	Person(){
		battle = false;
		live = true;
		needPersUPD = true;
		does = false;
		wait = false;
		stand = true;
		needPathUPD = false;
		needWeightUPD = false;
		active = true;
		needUPD = false;
		lastGeoPositionUPD = clock();
		lastPersRegen = clock();
		lastPersUPD = clock();
		lastBuffUPD = clock();
		lastMainUPD = clock();
		targetNumber = -1;
		animSpeed = 1;
		stan = false;
		dvig = false;
		UPD = "NULL";
		UI_UPD = "NULL";

		for (int i = 0; i < INVENTORYSLOTCOUNT; i++){
			inventory.push_back(InventorySlot());
		}
		for (int i = 0; i < 10; i++){
			buffs.push_back(Buff());
			debuffs.push_back(Buff());
		}
		status = idle;
		animStatus = animIdle;
		Mastery type1, type2;
		type1.lvlExp[0] = 0;
		type1.lvlExp[1] = 20;
		type1.lvlExp[2] = 30;
		type1.lvlExp[3] = 20;
		type1.lvlExp[4] = 70;
		type1.lvlExp[5] = 60;
		type1.lvlExp[6] = 100;
		type2.lvlExp[0] = 0;
		type2.lvlExp[1] = 10;
		type2.lvlExp[2] = 15;
		type2.lvlExp[3] = 20;
		type2.lvlExp[4] = 25;
		type2.lvlExp[5] = 30;
		type1.lvlExp[6] = 100;
		for (int i = 0; i < 7; i++){
			masteryList.push_back(Mastery(type1));
		}
		for (int i = 0; i < 3; i++){
			masteryList.push_back(Mastery(type2));
		}
		for (int i = 0; i < 44; i++){
			spellList.push_back(Spell());
		}
	}
	vector<Vector3> pathList;
	vector<InventorySlot> inventory;
	vector<Buff> buffs, debuffs;
	vector<Spell> spellList;
	PersonStatus status;
	AnimationStatus animStatus;
	string name, command, waitingCommand, dopCommand, UPD, UI_UPD;
	int race, persID, persType, freeCharacteristics, strength, agility, constitution, intelligence, wisdom, base_strength, base_agility,
		base_constitution, base_intelligence, base_wisdom, weaponSlot, bodySlot, critChance, critRate, recoveryHP,
		recoveryMP, failSpellChance, resistanceFire, resistanceCold, resistanceNegative, resistanceSlash, resistancePierce,
		resistanceCrush, attackSpeed, abilityPoint, spellPoint, characteristicPoint, useItemSlotNumber, waitingUseItemSlotNumber, targetNumber, 
		waitingTargetNumber, pickupNumber, waitingPickupNumber;
	float maxHP, curHP, maxMP, curMP, maxWeight, curWeight, visibleRange, speed, rotationSpeed, modStrength,
		modAgility, modConstitution, modIntelligence, modWisdom, minAttack, maxAttack, 
		evasion, accuracy, saveReaction, saveWill, savePersistence, complexitySpell, complexityAbility, invisible, detection, 
		concentration, regenHPInBattle, regenHPOutBattle, regenMPInBattle, regenMPOutBattle, attackRange, corpseSaveTime, saveDeath, 
		attackTime, animSpeed;
	
	Vector3 position, rotation, waitingMovePosition, movePosition;
	bool needPersUPD, live, battle, does, wait, stand, needPathUPD, stan, root, corpseSave, resInPlace, needWeightUPD, active, needUPD;
	unsigned int lastPersRegen, lastPersUPD, lastBuffUPD, lastGeoPositionUPD, lastMainUPD, lastAttackTime, battleTime, deadTime, dvig;
	PointsDrop pointDrop;
	vector<Drop> dropList;
	Data data, waitData, dopData, statsUpData;
	vector<Mastery> masteryList;
};



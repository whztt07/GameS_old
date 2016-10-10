#include "stdafx.h"

#include <string>

#include "Person.h"
#include "Global.h"

using namespace std;

BaseItemHolder *Person::baseItemHolder;

Person::Person() : spellList(SPELL_COUNT), masteryList(MASTERY_COUNT), buffList(BUFF_COUNT), debuffList(DEBUFF_COUNT),
inventory(INVENTORY_SIZE){}

void Person::UpdateSpellLvl(){
	int count = masteryList.GetMasteryCount();
	for (int i = 0; i < count; i++)
	if (masteryList.GetMastery(i).GetLvlUp())
		spellList.UpdateLvl(i, masteryList.GetMastery(i).GetLvl());
}

void Person::Init(BaseItemHolder &baseItemHolder){
	Person::baseItemHolder = &baseItemHolder;
}

void Person::UpdateStats(){
	/*
	float minAttack = 1, maxAttack = 2, attackSpeed = 600, critChance = 5, critRate = 2, attackRange = 1, accuracy = 4,
		speedPenalty = 0, failCastSpell = 0, evasionPenalty = 20, resSlash = 0, resCrush = 0, resPierce = 0, regenHPMod = 1,
		regenMPMod = 1, regenHPBonus = 0, regenMPBonus = 0, speedBonus = 0, bonusAttack = 0, bonusAttackRange = 0, bonusAttackSpeed = 0,
		bonusInvisible = 0, bonusDetection = 0, bonusConcentration = 0, bonusIntelligence = 0, bonusStrength = 0, bonusAgility = 0;
	bool root = false;

	if (weaponSlot > -1){
		Item weap = baseItemHolder->GetItem(weaponSlot);
		minAttack = weap.minAttack;
		maxAttack = weap.maxAttack;
		attackSpeed = weap.attackSpeed;
		critChance = weap.critChance;
		critRate = weap.critRate;
		attackRange = weap.rangeAttack;
		accuracy = weap.accuracy;
		if (weap.subType == "Sword"){
			int lvl = var->personList[j].masteryList[0].curLvl;
			bonusAttack += 1 * lvl;
			bonusAttackSpeed += 0.05 * lvl;
		}
		if (weap.subType == "Blunt"){
			int lvl = var->personList[j].masteryList[1].curLvl;
			bonusAttack += 1.5 * lvl;
			bonusAttackSpeed += 0.02 * lvl;
		}
		if (weap.subType == "Bow"){
			int lvl = var->personList[j].masteryList[2].curLvl;
			bonusAttack += 0.5 * lvl;
			bonusAttackSpeed += 0.03 * lvl;
			bonusAttackRange += 0.6 * lvl;
		}
	}



	if (var->personList[j].bodySlot > -1){
		Item armor = var->baseItemList[var->personList[j].bodySlot];
		speedPenalty = armor.speedPenalty;
		failCastSpell = armor.failCastSpell;
		evasionPenalty = armor.evasionPenalty;
		resSlash = armor.resSlash;
		resCrush = armor.resCrush;
		resPierce = armor.resPierce;
	}
	bonusInvisible = 2 * var->personList[j].masteryList[7].curLvl;
	bonusDetection = 2 * var->personList[j].masteryList[8].curLvl;
	bonusConcentration = 3 * var->personList[j].masteryList[9].curLvl;

	for (int i = 0; i < 10; i++){
		switch (var->personList[j].buffs[i].type)
		{
		case 300:
			regenHPMod *= 2;
			break;
		case 301:
			regenMPMod *= 2;
			break;
		case 400:
			speedBonus += -20;
			break;
		case 401:
			speedBonus += -50;
			break;
		case 402:
			root = true;
			break;
		default:
			break;
		}
	}

	if (var->personList[j].spellList[0].learn){
		bonusIntelligence += 2;
	}
	if (var->personList[j].spellList[1].learn){
		bonusAgility += 4;
	}
	if (var->personList[j].spellList[2].learn){
		bonusStrength -= 2;
	}
	if (var->personList[j].spellList[3].learn){
		bonusStrength += 4;
	}
	if (var->personList[j].spellList[4].learn){
		bonusAgility -= 2;
	}
	var->personList[j].strength = var->personList[j].base_strength + bonusStrength;
	var->personList[j].agility = var->personList[j].base_agility + bonusAgility;
	var->personList[j].constitution = var->personList[j].base_constitution;
	var->personList[j].intelligence = var->personList[j].base_intelligence + bonusIntelligence;
	var->personList[j].wisdom = var->personList[j].base_wisdom;

	if (var->personList[j].strength < 1)
		var->personList[j].strength = 1;

	if (var->personList[j].agility < 1)
		var->personList[j].agility = 1;

	if (var->personList[j].constitution < 1)
		var->personList[j].constitution = 1;

	if (var->personList[j].intelligence < 1)
		var->personList[j].intelligence = 1;

	if (var->personList[j].wisdom < 1)
		var->personList[j].wisdom = 1;

	var->personList[j].modStrength = (var->personList[j].strength - 10) / 2.0;
	var->personList[j].modAgility = (var->personList[j].agility - 10) / 2.0;
	var->personList[j].modConstitution = (var->personList[j].constitution - 10) / 2.0;
	var->personList[j].modIntelligence = (var->personList[j].intelligence - 10) / 2.0;
	var->personList[j].modWisdom = (var->personList[j].wisdom - 10) / 2.0;

	var->personList[j].maxHP = var->personList[j].constitution * 10;
	var->personList[j].maxMP = var->personList[j].wisdom * 20;
	var->personList[j].maxWeight = var->personList[j].strength * 10;

	if (var->personList[j].maxMP < 1)
		var->personList[j].maxMP = 1;

	if (var->personList[j].maxMP < 1)
		var->personList[j].maxMP = 1;

	if (var->personList[j].maxWeight < 1)
		var->personList[j].maxWeight = 1;

	var->personList[j].minAttack = minAttack + var->personList[j].modStrength + bonusAttack;
	var->personList[j].maxAttack = maxAttack + var->personList[j].modStrength + bonusAttack;

	if (var->personList[j].minAttack < 0)
		var->personList[j].minAttack = 0;

	if (var->personList[j].maxAttack < 0)
		var->personList[j].maxAttack = 0;

	var->personList[j].attackSpeed = attackSpeed * (1 + var->personList[j].modAgility*0.05 + bonusAttackSpeed);

	if (var->personList[j].attackSpeed < 100)
		var->personList[j].attackSpeed = 100;

	if (var->personList[j].attackSpeed > 1500)
		var->personList[j].attackSpeed = 1500;

	var->personList[j].critChance = critChance;
	var->personList[j].critRate = critRate;

	float modAgi = var->personList[j].modAgility;
	if (modAgi > evasionPenalty){
		modAgi = evasionPenalty;
	}
	var->personList[j].evasion = 10 + modAgi;
	var->personList[j].accuracy = accuracy + var->personList[j].modAgility;
	var->personList[j].speed = 3 * (1 + (speedBonus - speedPenalty) * 0.01);

	if (var->personList[j].speed < 1)
		var->personList[j].speed = 1;

	if (var->personList[j].speed > 5)
		var->personList[j].speed = 5;

	var->personList[j].saveReaction = var->personList[j].modAgility;
	var->personList[j].savePersistence = var->personList[j].modConstitution;
	var->personList[j].saveWill = var->personList[j].modWisdom;
	var->personList[j].saveDeath = var->personList[j].savePersistence + 2;
	var->personList[j].complexitySpell = 10 + var->personList[j].modIntelligence;
	var->personList[j].complexityAbility = 10 + var->personList[j].modStrength;

	if (var->personList[j].complexitySpell < 0)
		var->personList[j].complexitySpell = 0;

	if (var->personList[j].complexityAbility < 0)
		var->personList[j].complexityAbility = 0;

	var->personList[j].invisible = 10 + var->personList[j].modAgility + bonusInvisible;
	var->personList[j].detection = var->personList[j].modIntelligence + bonusDetection;
	var->personList[j].concentration = var->personList[j].modConstitution + bonusConcentration;
	var->personList[j].failSpellChance = failCastSpell;

	if (var->personList[j].failSpellChance < 0)
		var->personList[j].failSpellChance = 0;

	if (var->personList[j].failSpellChance > 95)
		var->personList[j].failSpellChance = 95;

	var->personList[j].rotationSpeed = var->personList[j].speed * 100 / 1.0;
	var->personList[j].attackRange = attackRange + bonusAttackRange;
	var->personList[j].recoveryHP = 100;
	var->personList[j].recoveryMP = 100 + 10 * var->personList[j].modIntelligence;

	if (var->personList[j].recoveryHP < 10)
		var->personList[j].recoveryHP = 10;

	if (var->personList[j].recoveryMP < 10)
		var->personList[j].recoveryMP = 10;

	var->personList[j].regenHPOutBattle = (var->personList[j].constitution / 2.0) * regenHPMod + regenHPBonus;
	var->personList[j].regenMPOutBattle = (var->personList[j].intelligence / 2.0) * regenMPMod + regenMPBonus;
	var->personList[j].regenHPInBattle = var->personList[j].regenHPOutBattle / 10.0;
	var->personList[j].regenMPInBattle = var->personList[j].regenMPOutBattle / 10.0;
	var->personList[j].resistanceCrush = resCrush;
	var->personList[j].resistanceSlash = resSlash;
	var->personList[j].resistancePierce = resPierce;
	var->personList[j].resistanceFire = 2;
	var->personList[j].resistanceCold = 2;
	var->personList[j].resistanceNegative = 2;

	var->personList[j].root = root;


	var->personList[j].needPersUPD = false;*/
}

void Person::SetName(const string &newName){
	name = newName;
}

void Person::SetRace(int  newRace){
	race = newRace;
}

void Person::SetBaseStrength(int  newBaseStrength){
	baseStrength = newBaseStrength;
}

void Person::SetBaseAgility(int  newBaseAgility){
	baseAgility = newBaseAgility;
}

void Person::SetBaseConstitution(int  newBaseConstitution){
	baseConstitution = newBaseConstitution;
}

void Person::SetBaseIntelligence(int  newBaseIntelligence){
	baseIntelligence = newBaseIntelligence;
}

void Person::SetBaseWisdom(int  newBaseWisdom){
	baseWisdom = newBaseWisdom;
}

void Person::SetFreeCharacteristics(int  newFreeCharacteristics){
	freeCharacteristics = newFreeCharacteristics;
}

void Person::SetWeaponSlot(int  newWeaponSlot){
	weaponSlot = newWeaponSlot;
}

void Person::SetBodySlot(int  newBodySlot){
	bodySlot = newBodySlot;
}

void Person::SetCurrentHp(float  newCurrentHp){
	currentHp = newCurrentHp;
}

void Person::SetCurrentMp(float  newCurrentMp){
	currentMp = newCurrentMp;
}

void Person::SetVisibleRange(float  newVisibleRange){
	visibleRange = newVisibleRange;
}


void Person::SetLive(bool  newLive){
	live = newLive;
}

void Person::SetResInPlace(bool  newResInPlace){
	resInPlace = newResInPlace;
}

void Person::SetCorpseSaveTime(float  newCorpseSaveTime){
	corpseSaveTime = newCorpseSaveTime;
}

void Person::SetPersonId(int  newPersId){
	personId = newPersId;
}

void Person::SetType(int  newType){
	type = newType;
}

void Person::SetPosition(const Vector3 &newPosition){
	position = newPosition;
}

void Person::SetRotation(float  newRotation){
	rotation = newRotation;
}


void Person::SetCharacteristicPoint(int  newCharacteristicPoint){
	characteristicPoint = newCharacteristicPoint;
}

void Person::SetAbilityPoint(int  newAbilityPoint){
	abilityPoint = newAbilityPoint;
}

void Person::SetSpellPoint(int  newSpellPoint){
	spellPoint = newSpellPoint;
}

void Person::SetActive(bool  newActive){
	active = newActive;
}

void Person::SetNeedUpdate(bool  newNeedUpdate){
	needUpdate = newNeedUpdate;
}

void Person::SetUpdate(const string &newUpdate){
	update = newUpdate;
}

void Person::SetWait(bool  newWait){
	wait = newWait;
}

void Person::SetCommand(const string &newCommand){
	command = newCommand;
}

void Person::SetFastCommand(const string &newFastCommand){
	fastCommand = newFastCommand;
}

void Person::SetWaitingCommand(const string &newWaitingCommand){
	waitingCommand = newWaitingCommand;
}

void Person::SetData(const Data &newData){
	data = newData;
}

void Person::SetFastData(const Data &newFastData){
	fastData = newFastData;
}

void Person::SetWaitingData(const Data &newWaitingData){
	waitingData = newWaitingData;
}

const int& Person::GetPersonId() const{
	return personId;
}

const string& Person::GetUpdate() const{
	return update;
}

const string& Person::GetUiUpdate() const{
	return uiUpdate;
}

const bool& Person::GetDoes() const{
	return does;
}

const int& Person::GetRace() const{
	return race;
}

const float& Person::GetCurrentHp() const{
	return currentHp;
}

const float& Person::GetCurrentMp() const{
	return currentMp;
}




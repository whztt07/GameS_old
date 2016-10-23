#include "stdafx.h"

#include <string>
#include <time.h>

#include "Person.h"
#include "Global.h"

using namespace std;

BaseItemHolder *Person::baseItemHolder;
BaseSpellHolder *Person::baseSpellHolder;
GeoData *Person::geoData;

int PRandom(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

float PRandomf(int min, int max){
	return (rand() % ((max - min) * 100 + 1)) / 100.0 + min;
}

Person::Person() : spellList(SPELL_COUNT), masteryList(MASTERY_COUNT), buffList(BUFF_COUNT), debuffList(DEBUFF_COUNT),
inventory(INVENTORY_SIZE){
	
	
	lastPersonUpdate = clock();
	targetPerson = NULL;
	
	update = "NULL";
	uiUpdate = "NULL";
	waitingCommand = "NULL";
	command = "NULL";
	fastCommand = "NULL";
	status = idle;
	animationStatus = animIdle;
	targetNumber = -1;
	useItemSlotNumber = -1;
	pickupNumber = -1;
	corpseSaveTime = 0;
	animationSpeed = 1;
	attackTime = 0;
	battleTime = 0;
	live = true;
	resInPlace = false;
	active = true;
	needUpdate = false;
	needStatsUpdate = true;
	needWeightUpdate = true;
	does = false;
	wait = false;
	corpseSave = true;
	needPathUpdate = false;
	stand = false;
	moving = false;
	battle = false;
	stan = false;
	_delete = false;

}

void Person::UpdateSpellLvl(){
	int count = masteryList.GetMasteryCount();
	for (int i = 0; i < count; i++)
	if (masteryList.GetMastery(i).GetLvlUp())
		spellList.UpdateLvl(i, masteryList.GetMastery(i).GetLvl());
}

void Person::Init(BaseItemHolder &baseItemHolder, BaseSpellHolder &baseSpellHolder, GeoData &geoData){
	Person::baseItemHolder = &baseItemHolder;
	Person::baseSpellHolder = &baseSpellHolder;
	Person::geoData = &geoData;
}
void Person::AddTargetPerson(Person &newTargetPerson){
	if (!targetPerson)
		targetPerson = &newTargetPerson;
}
void Person::SetTargetPerson(Person &newTargetPerson){
	
	targetPerson = &newTargetPerson;
}

void Person::UpdateAI(){
	if (type == 2 && targetPerson && status == idle) {
		status = r_attack;
	}
}

const string& Person::GetCommand() const{
	return command;
}

void Person::UpdateStats(){
	if (needStatsUpdate){
		float newMinAttack = 1, newMaxAttack = 2, newAttackSpeed = 600, newCritChance = 5, newCritRate = 2, newAttackRange = 1, newAccuracy = 4,
			speedPenalty = 0, newFailCastSpell = 0, evasionPenalty = 20, newResistanceSlash = 0, newResistanceCrush = 0,
			newResistancePierce = 0, regenHPMod = 1, regenMPMod = 1, regenHPBonus = 0, regenMPBonus = 0, speedBonus = 0, bonusAttack = 0,
			bonusAttackRange = 0, bonusAttackSpeed = 0, bonusInvisible = 0, bonusDetection = 0, bonusConcentration = 0, bonusIntelligence = 0,
			bonusStrength = 0, bonusAgility = 0;
		bool newRoot = false;

		if (weaponSlot > -1){
			Item weap = baseItemHolder->GetItem(weaponSlot);
			newMinAttack = weap.GetMinAttack();
			newMaxAttack = weap.GetMaxAttack();
			newAttackSpeed = weap.GetAttackSpeed();
			newCritChance = weap.GetCritChance();
			newCritRate = weap.GetCritRate();
			newAttackRange = weap.GetRangeAttack();
			newAccuracy = weap.GetAccuracy();
			if (weap.GetSubType() == "Sword"){
				int lvl = masteryList.GetMastery(0).GetLvl();
				bonusAttack += 1 * lvl;
				bonusAttackSpeed += 0.05 * lvl;
			}
			if (weap.GetSubType() == "Blunt"){
				int lvl = masteryList.GetMastery(1).GetLvl();
				bonusAttack += 1.5 * lvl;
				bonusAttackSpeed += 0.02 * lvl;
			}
			if (weap.GetSubType() == "Bow"){
				int lvl = masteryList.GetMastery(2).GetLvl();
				bonusAttack += 0.5 * lvl;
				bonusAttackSpeed += 0.03 * lvl;
				bonusAttackRange += 0.6 * lvl;
			}
		}



		if (bodySlot > -1){
			Item armor = baseItemHolder->GetItem(bodySlot);
			speedPenalty = armor.GetSpeedPenalty();
			newFailCastSpell = armor.GetFailCastSpell();
			evasionPenalty = armor.GetEvasionPenalty();
			newResistanceSlash = armor.GetResistSlash();
			newResistanceCrush = armor.GetResistCrush();
			newResistancePierce = armor.GetResistPierce();
		}
		bonusInvisible = 2 * masteryList.GetMastery(7).GetLvl();
		bonusDetection = 2 * masteryList.GetMastery(8).GetLvl();
		bonusConcentration = 3 * masteryList.GetMastery(9).GetLvl();

		for (int i = 0; i < BUFF_COUNT; i++){
			switch (buffList.GetBuff(i).GetType())
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

		if (spellList.GetSpell(0).GetLearn()){
			bonusIntelligence += 2;
		}
		if (spellList.GetSpell(1).GetLearn()){
			bonusAgility += 4;
		}
		if (spellList.GetSpell(2).GetLearn()){
			bonusStrength -= 2;
		}
		if (spellList.GetSpell(3).GetLearn()){
			bonusStrength += 4;
		}
		if (spellList.GetSpell(4).GetLearn()){
			bonusAgility -= 2;
		}
		strength = baseStrength + bonusStrength;
		agility = baseAgility + bonusAgility;
		constitution = baseConstitution;
		intelligence = baseIntelligence + bonusIntelligence;
		wisdom = baseWisdom;

		if (strength < 1)
			strength = 1;

		if (agility < 1)
			agility = 1;

		if (constitution < 1)
			constitution = 1;

		if (intelligence < 1)
			intelligence = 1;

		if (wisdom < 1)
			wisdom = 1;

		modStrength = (strength - 10) / 2.0;
		modAgility = (agility - 10) / 2.0;
		modConstitution = (constitution - 10) / 2.0;
		modIntelligence = (intelligence - 10) / 2.0;
		modWisdom = (wisdom - 10) / 2.0;

		maxHp = constitution * 10;
		maxMp = wisdom * 20;
		maxWeight = strength * 10;

		if (maxMp < 1)
			maxMp = 1;

		if (maxMp < 1)
			maxMp = 1;

		if (maxWeight < 1)
			maxWeight = 1;

		minAttack = newMinAttack + modStrength + bonusAttack;
		maxAttack = newMaxAttack + modStrength + bonusAttack;

		if (minAttack < 0)
			minAttack = 0;

		if (maxAttack < 0)
			maxAttack = 0;

		attackSpeed = newAttackSpeed * (1 + modAgility*0.05 + bonusAttackSpeed);

		if (attackSpeed < 100)
			attackSpeed = 100;

		if (attackSpeed > 1500)
			attackSpeed = 1500;

		critChance = newCritChance;
		critRate = newCritRate;

		float modAgi = modAgility;
		if (modAgi > evasionPenalty){
			modAgi = evasionPenalty;
		}
		evasion = 10 + modAgi;
		accuracy = newAccuracy + modAgility;
		speed = 3 * (1 + (speedBonus - speedPenalty) * 0.01);

		if (speed < 1)
			speed = 1;

		if (speed > 5)
			speed = 5;

		saveReaction = modAgility;
		savePersistence = modConstitution;
		saveWill = modWisdom;
		saveDeath = savePersistence + 2;
		complexitySpell = 10 + modIntelligence;
		complexityAbility = 10 + modStrength;

		if (complexitySpell < 0)
			complexitySpell = 0;

		if (complexityAbility < 0)
			complexityAbility = 0;

		invisible = 10 + modAgility + bonusInvisible;
		detection = modIntelligence + bonusDetection;
		concentration = modConstitution + bonusConcentration;
		failSpellChance = newFailCastSpell;

		if (failSpellChance < 0)
			failSpellChance = 0;

		if (failSpellChance > 95)
			failSpellChance = 95;

		rotationSpeed = speed * 100 / 1.0;
		attackRange = newAttackRange + bonusAttackRange;
		recoveryHp = 100;
		recoveryMp = 100 + 10 * modIntelligence;

		if (recoveryHp < 10)
			recoveryHp = 10;

		if (recoveryMp < 10)
			recoveryMp = 10;

		regenHpOutBattle = (constitution / 2.0) * regenHPMod + regenHPBonus;
		regenMpOutBattle = (intelligence / 2.0) * regenMPMod + regenMPBonus;
		regenHpInBattle = regenHpOutBattle / 10.0;
		regenMpInBattle = regenMpOutBattle / 10.0;
		resistanceCrush = newResistanceCrush;
		resistanceSlash = newResistanceSlash;
		resistancePierce = newResistancePierce;
		resistanceFire = 2;
		resistanceCold = 2;
		resistanceNegative = 2;
		root = newRoot;

		needStatsUpdate = false;
	}
}

void Person::UpdateWeight(){
	if (needWeightUpdate){
		currentWeight = 0;
		for (int i = 0; i < INVENTORY_SIZE; i++){
			if (inventory.GetSlot(i).GetItemId() != -1)
				currentWeight += baseItemHolder->GetItem(inventory.GetSlot(i).GetItemId()).GetWeight();
		}
		currentWeight += baseItemHolder->GetItem(weaponSlot).GetWeight();
		currentWeight += baseItemHolder->GetItem(bodySlot).GetWeight();
		float cur = currentWeight * 100.0 / maxWeight;
		buffList.DeleteBuff(400);
		buffList.DeleteBuff(401);
		buffList.DeleteBuff(402);
		if (cur >= 60 && cur < 80){
			buffList.AddBuff(400, 0);
		}
		if (cur >= 80 && cur < 100){
			buffList.AddBuff(401, 0);
		}
		if (cur >= 100){
			buffList.AddBuff(402, 0);
		}
		needWeightUpdate = false;
		needStatsUpdate = true;
	}
}

void Person::UpdateBuff(float deltaTime){
	buffList.UpdateBuffs(deltaTime);
	debuffList.UpdateBuffs(deltaTime);
}

void Person::UpdateCommand(){

	if (command == "Move"){
		command = "";
		status = r_move;
		movePosition = Vector3(data.data1, data.data2, data.data3);
		needPathUpdate = true;
	}
	if (command == "Attack"){
		command = "GetTarget";
		status = r_attack;
		targetNumber = data.data1;

	}
	if (command == "Cast"){
		command = "";


	}
	if (command == "UseItem"){
		command = "";
		status = useItem;
		useItemSlotNumber = data.data1;
	}
	if (command == "Pickup"){
		command = "";
		status = r_pickup;
		pickupNumber = data.data1;
	}
	if (command == "Resurrection"){
		command = "";
		status = res;
	}
	if (command == "ResurrectionInPlace"){
		command = "";
		status = resplace;
	}
	if (command == "DropItem"){
		command = "";

	}
	if (command == "Dialog"){
		command = "";

	}
	if (command == "StatsUP"){
		command = "";
		status = statsUp;
		statsUpData = data;
	}

}

const int& Person::GetTargetNumber() const{
	return targetNumber;
}

const bool&	Person::IsDead() const{
	return !live;
}

const bool&	Person::IsLive() const{
	return live;
}

void Person::SetCorpseSave(bool newCorpseSave){
	corpseSave = newCorpseSave;
}

const int& Person::GetType() const{
	return type;
}

bool Person::IsFullDead() const{
	return clock() - deadTime > corpseSaveTime ? true : false;
}
const Vector3& Person::GetLastPath() const{
	return pathList.back();
}
const float & Person::GetAttackRange() const{
	return attackRange;
}

bool Person::StartClientUpdate(){
	if (needUpdate){
		update = "AllUPD|" + to_string(personId) + "|" + name + "|"
			+ to_string(live) + "|" + to_string(corpseSave) + "|"
			+ to_string(resInPlace) + "|" + to_string(position.x) + "|"
			+ to_string(position.y) + "|" + to_string(position.z) + "|"
			+ to_string(rotation) + "|" + to_string(currentHp) + "|"
			+ to_string(maxHp) + "|" + to_string(currentMp) + "|"
			+ to_string(maxMp) + "|" + to_string(animationStatus) + "|"
			+ to_string(animationSpeed) + "|" + to_string(targetNumber) + "|";


		string ss = "UIUPD|" + to_string(baseStrength) + "|" + to_string(baseAgility) + "|"
			+ to_string(baseConstitution) + "|" + to_string(baseIntelligence) + "|"
			+ to_string(baseWisdom) + "|"
			+ to_string(strength) + "|" + to_string(agility) + "|"
			+ to_string(constitution) + "|" + to_string(intelligence) + "|"
			+ to_string(wisdom) + "|" + to_string(modStrength) + "|"
			+ to_string(modAgility) + "|" + to_string(modConstitution) + "|"
			+ to_string(modIntelligence) + "|" + to_string(modWisdom) + "|"
			+ to_string(minAttack) + "|" + to_string(maxAttack) + "|"
			+ to_string(attackSpeed) + "|" + to_string(critChance) + "|"
			+ to_string(critRate) + "|" + to_string(evasion) + "|"
			+ to_string(accuracy) + "|" + to_string(speed) + "|"
			+ to_string(saveReaction) + "|" + to_string(savePersistence) + "|"
			+ to_string(saveWill) + "|" + to_string(saveDeath) + "|"
			+ to_string(complexitySpell) + "|" + to_string(complexityAbility) + "|"
			+ to_string(invisible) + "|" + to_string(detection) + "|"
			+ to_string(concentration) + "|" + to_string(failSpellChance) + "|"
			+ to_string(rotationSpeed) + "|" + to_string(visibleRange) + "|"
			+ to_string(attackRange) + "|" + to_string(recoveryHp) + "|"
			+ to_string(recoveryMp) + "|" + to_string(regenHpOutBattle) + "|"
			+ to_string(regenMpOutBattle) + "|" + to_string(regenHpInBattle) + "|"
			+ to_string(regenMpInBattle) + "|" + to_string(resistanceSlash) + "|"
			+ to_string(resistanceCrush) + "|" + to_string(resistancePierce) + "|"
			+ to_string(resistanceFire) + "|" + to_string(resistanceCold) + "|"
			+ to_string(resistanceNegative) + "|" + to_string(freeCharacteristics) + "|"
			+ to_string(currentWeight) + "|" + to_string(maxWeight) + "|"
			+ to_string(characteristicPoint) + "|" + to_string(abilityPoint) + "|"
			+ to_string(spellPoint) + "|" + to_string(weaponSlot) + "|"
			+ to_string(bodySlot) + "|";

		for (int j = 0; j < INVENTORY_SIZE; j++){
			ss += to_string(inventory.GetSlot(j).GetItemId()) + "|" + to_string(inventory.GetSlot(j).GetCount()) + "|";
		}
		for (int j = 0; j < BUFF_COUNT; j++){
			ss += to_string(buffList.GetBuff(j).GetType()) + "|";
		}
		for (int j = 0; j < DEBUFF_COUNT; j++){
			ss += to_string(debuffList.GetBuff(j).GetType()) + "|";
		}
		for (int j = 0; j < MASTERY_COUNT; j++){
			ss += to_string(masteryList.GetMastery(j).GetLvl()) + "|" + to_string(masteryList.GetMastery(j).GetExp()
				/ Mastery::GetLvlExp(masteryList.GetMastery(j).GetLvl() + 1)) + "|";
		}
		int num = 0;
		string dopcurstring = "";
		for (int j = 0; j < ABILITY_COUNT; j++){
			if (spellList.GetSpell(j).GetLearn()){
				num++;
				dopcurstring += to_string(j) + "|" + to_string(spellList.GetSpell(j).GetLvl()) + "|"
					+ to_string(baseSpellHolder->GetSpell(j).GetCooldown() > 0 ?
					spellList.GetSpell(j).GetCooldown() / baseSpellHolder->GetSpell(j).GetCooldown() : 0) + "|";
			}
		}
		ss += to_string(num) + "|" + dopcurstring;
		num = 0;
		dopcurstring = "";
		for (int j = ABILITY_COUNT; j < SPELL_COUNT; j++){
			if (spellList.GetSpell(j).GetLearn()){
				num++;
				dopcurstring += to_string(j) + "|" + to_string(spellList.GetSpell(j).GetLvl()) + "|"
					+ to_string(baseSpellHolder->GetSpell(j).GetCooldown() > 0 ? 
					spellList.GetSpell(j).GetCooldown() / baseSpellHolder->GetSpell(j).GetCooldown() : 0) + "|";
			}

		}
		ss += to_string(num) + "|" + dopcurstring;
		uiUpdate = ss;
		needUpdate = false;
		return true;
	}
	else{
		return false;
	}
}

string Person::NeedClientUpdate(const Vector3 &personPosition, float visibleRange){
	if (Vector3::Distance(position, personPosition) <= visibleRange){
		return to_string(personId) + "|" + name + "|"
			+ to_string(live) + "|" + to_string(position.x) + "|"
			+ to_string(position.y) + "|" + to_string(position.z) + "|"
			+ to_string(rotation) + "|"
			+ to_string(currentHp / maxHp) + "|" + to_string(animationStatus) + "|"
			+ to_string(animationSpeed) + "|";
	}
	else{
		return "NULL";
	}
}

void Person::FinishClientUpdate(const string &updateInfo){
	update += updateInfo;
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

void Person::SetStatus(int newStatus){
	status = newStatus;
}

void Person::SetStand(bool newStand){
	stand = newStand;
}

void Person::SetPathList(const vector<Vector3> &newPathList){
	pathList = newPathList;
}

void Person::SetNeedPathUpdate(bool newNeedPathUpdate){
	needPathUpdate = newNeedPathUpdate;
}

void Person::SetMoving(bool newMoving){
	moving = newMoving;
}


const int& Person::GetPersonId() const{
	return personId;
}

const string& Person::GetUiUpdate() const{
	return uiUpdate;
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

const Vector3& Person::GetPosition() const{
	return position;
}

const float& Person::GetVisibleRange() const{
	return visibleRange;
}

const bool& Person::GetRoot() const{
	return root;
}

const float& Person::GetSpeed() const{
	return speed;
}

const int& Person::GetStatus() const{
	return status;
}

const Vector3& Person::GetMovePosition() const{
	return movePosition;
}

const float& Person::GetRotation() const{
	return rotation;
}

const float& Person::GetRotationSpeed() const{
	return rotationSpeed;
}

const Vector3& Person::GetFirstPath() const{
	return pathList[0];
}

int Person::GetPathListSize() const{
	return pathList.size();
}

const bool& Person::GetNeedPathUpdate() const{
	return needPathUpdate;
}


void Person::DeleteFirstPath(){
	pathList.erase(pathList.begin() + 0);
}



void Person::UpdateAnimation(){

	animationSpeed = 1.0;
	switch (status){
	case idle:
		if (battle){
			animationStatus = animWarIdle;
		}
		else{
			animationStatus = animIdle;
		}
		break;
	case r_attack:
	case r_move:
	case r_pickup:
		if (moving && !root && !stan){
			if (speed > 1.5){
				animationStatus = animRun;
				animationSpeed = speed / 3.0;
			}
			else{
				animationStatus = animWalk;
				animationSpeed = speed / 1.5;
			}
		}
		else{
			if (battle){
				animationStatus = animWarIdle;
			}
			else{
				animationStatus = animIdle;
			}
		}
		break;

	case _move:
	case move_attack:
	case move_pickup:
		if (root || stan){
			if (battle){
				animationStatus = animWarIdle;
			}
			else{
				animationStatus = animIdle;
			}
		}
		else{
			if (speed > 1.5){
				animationStatus = animRun;
				animationSpeed = speed / 3.0;
			}
			else{
				animationStatus = animWalk;
				animationSpeed = speed / 1.5;
			}
		}
		break;

	case attack:
		if (baseItemHolder->GetItem(weaponSlot).GetSubType() == "Bow"){
			animationStatus = animRangeAttack;
		}
		else{
			animationStatus = animAttack;
		}
		animationSpeed = 1.0 / attackTime;
		break;

	case dead:

		animationStatus = animDead;

		break;
	}

}


void Person::UpdateAction(float deltaTime){	
	if (geoData->FallingPerson(deltaTime, *this)){
	Vector3 targPos;
	int itemIndex;
	switch (status){
	case r_move:
	if (needPathUpdate){
	geoData->NeedPersonPath(*this, movePosition);
	needPathUpdate = false;
	moving = false;
	}
	else{
	if (geoData->Rotate(deltaTime, *this, pathList[0]))
	status = _move;
	}
	break;
	case _move:
	moving = true;
	geoData->MovePerson(deltaTime, *this);
	break;
	
	case r_attack:
		if (targetPerson->live && !targetPerson->_delete){
			if (Vector3::Distance(position, targetPerson->position) <= attackRange){
				if (geoData->Rotate(deltaTime, *this, targetPerson->position))
					status = attack;
			}
			else{
				if (pathList.size() == 0 || Vector3::Distance(targetPerson->position, pathList.back()) > 0.5){
					geoData->NeedPersonPath(*this, targetPerson->position);
					needPathUpdate = false;
					moving = false;
				}
				if (geoData->Rotate(deltaTime, *this, pathList[0]))
					status = move_attack;
			}
		}
		else{
			status = idle;
			targetPerson = NULL;
		}
	break;
	case move_attack:
		if (targetPerson->live && !targetPerson->_delete){
			if (Vector3::Distance(position, targetPerson->position) <= attackRange){
				status = r_attack;
			}
			else{
				if (pathList.size() == 0 || Vector3::Distance(targetPerson->position, pathList.back()) > 0.5){
					geoData->NeedPersonPath(*this, targetPerson->position);
					status = r_attack;
				}
				else{
					moving = true;
					geoData->MovePerson(deltaTime, *this);
				}
			}
		}
		else{
			status = idle;
			targetPerson = NULL;
		}
		break;
	case attack:
		if (targetPerson->live && !targetPerson->_delete){
			geoData->Rotate(deltaTime, *this, targetPerson->position);
			Attack();
		}
		else{
			status = idle;
			targetPerson = NULL;
		}
	break;
	/*
	case r_pickup:
	itemIndex = GetItemIndex(var->personList[i].pickupNumber);
	if (itemIndex == -1){
	var->personList[i].status = idle;
	}
	else{
	targPos = var->dropItemList[itemIndex].position;
	if (Vector3::Distance(var->personList[i].position, targPos) <= 0.2){
	GeoDvig::TargetItemRotation(deltaTime, i);
	}
	else{
	if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.2){
	GeoDvig::NeedPersonPath(i, targPos);
	var->personList[i].dvig = false;
	}
	GeoDvig::MoveRotation(deltaTime, i);
	}
	}
	break;
	case move_pickup:
	itemIndex = GetItemIndex(var->personList[i].pickupNumber);
	if (itemIndex == -1){
	var->personList[i].status = idle;
	}
	else{
	targPos = var->dropItemList[itemIndex].position;
	if (Vector3::Distance(var->personList[i].position, targPos) <= 0.2){
	var->personList[i].status = r_pickup;
	}
	else{
	var->personList[i].dvig = true;
	GeoDvig::MovePerson(deltaTime, i);
	}
	}
	break;
	case pickup:
	Pickup(i);
	break;
	*/
	case res:
		Resurrection();
		break;
	case statsUp:
	StatsUp();
	break;
	case useItem:
	UseItem();
	break;
	}
	}
	else{
	switch (status){

	case _move:
	status = r_move;
	break;
	case move_attack:
		status = r_attack;
	break;
	case move_pickup:
		status = r_pickup;
	break;
	default:
		status = idle;
	break;
	}
	}
}

void Person::Resurrection(bool place){
	Vector3 resPos = Vector3(1, 0, 1);
	if (!place)
		position = resPos;
	corpseSave = true;
	live = true;
	currentHp = maxHp / 2;
	status = idle;
}

void Person::Attack(){


	if (!does){
		attackTime = 750.0 / attackSpeed;
		does = true;
		lastAttackTime = clock();
	}
	else{
		float time = (clock() - lastAttackTime) / 1000.0;
		if (time >= attackTime){
			status = r_attack; 
			battle = true;
			battleTime = clock();
			if (PRandom(1, 20) + accuracy >= targetPerson->evasion){				
				targetPerson->battle = true;
				targetPerson->battleTime = clock();
				targetPerson->AddTargetPerson(*this);
				int mod = 1;
				if (PRandom(0, 100) <= critChance)
					mod = critRate;
				float damage = PRandom(minAttack, maxAttack) * mod;
				damage -= targetPerson->resistanceCrush;
				if (damage > 0)
					targetPerson->currentHp -= damage;
				if (targetPerson->currentHp <= 0 && targetPerson->live){
					targetPerson->currentHp = 0;
					targetPerson->Kill(*this);
				}
			}
			does = false;
			if (wait){
				wait = false;
				status = idle;
				command = waitingCommand;
				data = waitingData;
			}
		}
	}
}


void Person::Kill(Person &killer){
	killer.status = idle;
	status = dead;
	live = false;
	corpseSaveTime = 15000;
	deadTime = clock();
	does = false;

	/*if (persType == 2){
		for (int i = 0; i < dropList.size(); i++){
			if (Random(0, 100) <= dropList[i].chance){
				int count = Random(dropList[i].minCount, dropList[i].maxCount);
				float offsetX = Randomf(-1, 1), offsetZ = Randomf(-1, 1);
				DropItems(dropList[i].item, count, Vector3(position.x + offsetX, position.y, position.z + offsetZ));
			}
		}
		if (Random(0, 100) <= pointDrop.totalChance){
			int chance = Random(0, 100);
			int count = Random(pointDrop.minCount, pointDrop.maxCount);
			if (chance <= pointDrop.chanceCharacteristics){
				killer.AddPoints(count, 0, 0);
			}
			else if (chance <= pointDrop.chanceAbility){
				killer.AddPoints(0, count, 0);
			}
			else{
				killer.AddPoints(0, 0, count);
			}
		}
	}*/

	if (killer.targetPerson == this){
		killer.targetPerson = NULL;
	}
}
void Person::UpdateRegeneration(float deltaTime){
	if (live){
		float regen;
		if (battle){
			regen = regenHpInBattle;
		}
		else{
			regen = regenHpOutBattle;
		}
		regen *= deltaTime;
		if (regen > 0 && currentHp < maxHp){
			currentHp += regen;
			if (currentHp > maxHp){
				currentHp = maxHp;
			}
		}
		if (regen < 0 && currentHp > 1){
			currentHp += regen;
			if (currentHp < 1){
				currentHp = 1;
			}
		}

		if (battle){
			regen = regenMpInBattle;
		}
		else{
			regen = regenMpOutBattle;
		}
		regen *= deltaTime;
		if (regen > 0 && currentMp < maxMp){
			currentMp += regen;
			if (currentMp > maxMp){
				currentMp = maxMp;
			}
		}
		if (regen < 0 && currentMp > 1){
			currentMp += regen;
			if (currentMp < 1){
				currentMp = 1;
			}
		}
	}
}

bool Person::PersonActive(){
	if(!active)
	return clock() - lastPersonUpdate > 10000 ? false : true;
	return true;
}

string Person::NeedUpdate(){	
	lastPersonUpdate = clock();
	if (update == "NULL"){
		needUpdate = true;;
	}
	string s = update;  
	update = "NULL";
	return s;
}

void Person::Command(const string &command, const Data &data, bool fast){
	
	if (!fast){
		if (does){
			wait = true;
			waitingCommand = command;
			waitingData = data;
		}
		else{
			this->data = data;
			this->command = command;
		}
	}
	else{
		fastCommand = command;
		fastData = data;
	}
}


const bool& Person::GetLive() const{
	return live;
}


void Person::UpdateBattleStatus(){
	if (battle && clock() - battleTime > 10000)
		battle = false;
}
			
const bool& Person::GetBattle() const{
	return battle;
}

const bool& Person::IsDelete() const{
	return _delete;
}

void Person::SetDelete(bool newDelete) {
	_delete = newDelete;
}

void Person::StatsUp(){

	int str = statsUpData.data1, agi = statsUpData.data2, con = statsUpData.data3, intel = statsUpData.data4, wis = statsUpData.data5;

	int free = freeCharacteristics, _str = baseStrength, _agi = baseAgility, _con = baseConstitution, _intel = baseIntelligence, 
		_wis = baseWisdom;

	for (int i = 0; i < str; i++){
		int mod = (_str - 10) / 2;
		if (mod < 1)
			mod = 1;
		if (free < mod){

			return;
		}
		free -= mod;
		_str++;
	}
	for (int i = 0; i < agi; i++){
		int mod = (_agi - 10) / 2;
		if (mod < 1)
			mod = 1;
		if (free < mod){

			return;
		}
		free -= mod;
		_agi++;
	}
	for (int i = 0; i < con; i++){
		int mod = (_con - 10) / 2;
		if (mod < 1)
			mod = 1;
		if (free < mod){

			return;
		}
		free -= mod;
		_con++;
	}
	for (int i = 0; i < intel; i++){
		int mod = (_intel - 10) / 2;
		if (mod < 1)
			mod = 1;
		if (free < mod){

			return;
		}
		free -= mod;
		_intel++;
	}
	for (int i = 0; i < wis; i++){
		int mod = (_wis - 10) / 2;
		if (mod < 1)
			mod = 1;
		if (free < mod){

			return;
		}
		free -= mod;
		_wis++;
	}

	freeCharacteristics = free;
	baseStrength = _str;
	baseAgility = _agi;
	baseConstitution = _con;
	baseIntelligence = _intel;
	baseWisdom = _wis;
	needStatsUpdate = true;
	status = idle;
}


void Person::UseItem(){

	if (useItemSlotNumber < 0){
		if (useItemSlotNumber == -1 && weaponSlot != -1){
			int freeSlot = inventory.FreeInventorySlot();

			if (freeSlot == -1){

				status = idle;

				return;
			}
			else{
				inventory.GetSlot(freeSlot).SetItemId(weaponSlot);
				inventory.GetSlot(freeSlot).SetCount(1);
				weaponSlot = -1;
				needStatsUpdate = true;
			}
		}
		if (useItemSlotNumber == -2 && bodySlot != -1){
			int freeSlot = inventory.FreeInventorySlot();
			if (freeSlot == -1){

				status = idle;

				return;
			}
			else{
				inventory.GetSlot(freeSlot).SetItemId(bodySlot);
				inventory.GetSlot(freeSlot).SetCount(1);
				bodySlot = -1;
				needStatsUpdate = true;
			}
		}
	}
	else{
		if (inventory.GetSlot(useItemSlotNumber).GetItemId() != -1){
			string type = baseItemHolder->GetItem(inventory.GetSlot(useItemSlotNumber).GetItemId()).GetType();
			if (type == "Weapon"){

				int item = weaponSlot;
				weaponSlot = inventory.GetSlot(useItemSlotNumber).GetItemId();
				inventory.GetSlot(useItemSlotNumber).SetItemId(-1);
				inventory.GetSlot(useItemSlotNumber).SetCount(0);
				needStatsUpdate = true;
				if (item > -1){
					int freeSlot = inventory.FreeInventorySlot();

					inventory.GetSlot(freeSlot).SetItemId(item);
					inventory.GetSlot(freeSlot).SetCount(1);
				}
			}
			if (type == "Armor"){

				int item = bodySlot;
				bodySlot = inventory.GetSlot(useItemSlotNumber).GetItemId();
				inventory.GetSlot(useItemSlotNumber).SetItemId(-1);
				inventory.GetSlot(useItemSlotNumber).SetCount(0);
				needStatsUpdate= true;
				if (item > -1){
					int freeSlot = inventory.FreeInventorySlot();

					inventory.GetSlot(freeSlot).SetItemId(item);
					inventory.GetSlot(freeSlot).SetCount(1);
				}

			}
			if (type == "Potion"){
				string subType = baseItemHolder->GetItem(inventory.GetSlot(useItemSlotNumber).GetItemId()).GetSubType();
				inventory.TakeItem(useItemSlotNumber);
				needWeightUpdate = true;
				if (subType == "HP"){
					needStatsUpdate = true;
					buffList.AddBuff(300, 5);
					if (currentHp < maxHp){
						currentHp += 50 * recoveryHp / 100;
						if (currentHp > maxHp){
							currentHp = maxHp;
						}
					}
				}
				if (subType == "MP"){
					needStatsUpdate = true;
					buffList.AddBuff(301, 5);
					if (currentMp < maxMp){
						currentMp += 50 * recoveryMp / 100;
						if (currentMp > maxMp){
							currentMp = maxMp;
						}
					}
				}
			}
		}
	}

	status = idle;

}





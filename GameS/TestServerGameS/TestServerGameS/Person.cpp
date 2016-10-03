#include "stdafx.h"

#include <string>

#include "Person.h"
#include "Global.h"

using namespace std;

Person::Person() : spellList(SPELL_COUNT), masteryList(MASTERY_COUNT), buffList(BUFF_COUNT), debuffList(DEBUFF_COUNT),
inventory(INVENTORY_SIZE){}

void Person::UpdateSpellLvl(){
	int count = masteryList.GetMasteryCount();
	for (int i = 0; i < count; i++)
	if (masteryList.GetMastery(i).GetLvlUp())
		spellList.UpdateLvl(i, masteryList.GetMastery(i).GetLvl());
}

void Person::SetName(const string &_name){
	name = _name;
}

void Person::SetRace(const int &_race){
	race = _race;
}

void Person::SetBaseStrength(const int &_base_strength){
	base_strength = _base_strength;
}

void Person::SetBaseAgility(const int &_base_agility){
	base_agility = _base_agility;
}

void Person::SetBaseConstitution(const int &_base_constitution){
	base_constitution = _base_constitution;
}

void Person::SetBaseIntelligence(const int &_base_intelligence){
	base_intelligence = _base_intelligence;
}

void Person::SetBaseWisdom(const int &_base_wisdom){
	base_wisdom = _base_wisdom;
}

void Person::SetFreeCharacteristics(const int &_freeCharacteristics){
	freeCharacteristics = _freeCharacteristics;
}

void Person::SetWeaponSlot(const int &_weaponSlot){
	weaponSlot = _weaponSlot;
}

void Person::SetBodySlot(const int &_bodySlot){
	bodySlot = _bodySlot;
}

void Person::SetCurHp(const float &_curHp){
	curHp = _curHp;
}

void Person::SetCurMp(const float &_curMp){
	curMp = _curMp;
}

void Person::SetVisibleRange(const float &_visibleRange){
	visibleRange = _visibleRange;
}


void Person::SetLive(const bool &_live){
	live = _live;
}

void Person::SetResInPlace(const bool &_resInPlace){
	resInPlace = _resInPlace;
}

void Person::SetCorpseSaveTime(const float &_corpseSaveTime){
	corpseSaveTime = _corpseSaveTime;
}

void Person::SetPersId(const int &_persId){
	persId = _persId;
}

void Person::SetType(const int &_type){
	type = _type;
}

void Person::SetPosition(const Vector3 &pos){
	position = pos;
}

void Person::SetRotation(const float &rot){
	rotation = rot;
}


void Person::SetCharacteristicPoint(const int &_characteristicPoint){
	characteristicPoint = _characteristicPoint;
}

void Person::SetAbilityPoint(const int &_abilityPoint){
	abilityPoint = _abilityPoint;
}

void Person::SetSpellPoint(const int &_spellPoint){
	spellPoint = _spellPoint;
}

void Person::SetActive(const bool &_active){
	active = _active;
}

const string& Person::GetName() const{
	return name;
}

const int& Person::GetRace() const{
	return race;
}

const int& Person::GetBaseStrength() const{
	return base_strength;
}

const int& Person::GetBaseAgility() const{
	return base_agility;
}

const int& Person::GetBaseConstitution() const{
	return base_constitution;
}

const int& Person::GetBaseIntelligence() const{
	return base_intelligence;
}

const int& Person::GetBaseWisdom() const{
	return base_wisdom;
}

const int& Person::GetFreeCharacteristics() const{
	return freeCharacteristics;
}

const int& Person::GetWeaponSlot() const{
	return weaponSlot;
}

const int& Person::GetBodySlot() const{
	return bodySlot;
}

const float& Person::GetCurHp() const{
	return curHp;
}

const float& Person::GetCurMp() const{
	return curMp;
}

const float& Person::GetVisibleRange() const{
	return visibleRange;
}


const bool& Person::GetLive() const{
	return live;
}

const bool& Person::GetResInPlace() const{
	return resInPlace;
}

const float& Person::GetCorpseSaveTime() const{
	return corpseSaveTime;
}

const int& Person::GetPersId() const{
	return persId;
}

const int& Person::GetType() const{
	return type;
}

const Vector3& Person::GetPosition() const{
	return position;
}

const float& Person::GetRotation() const{
	return rotation;
}


const int& Person::GetCharacteristicPoint() const{
	return characteristicPoint;
}

const int& Person::GetAbilityPoint() const{
	return abilityPoint;
}

const int& Person::GetSpellPoint() const{
	return spellPoint;
}
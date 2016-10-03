#include "stdafx.h"

#include <string>

#include "WorkMSQL.h"
#include "MSQLConnect.h"
#include "Person.h"
#include "Item.h"
#include "SpellInfo.h"
#include "Mastery.h"
#include "MSQL_init_data.h"
#include "Spell.h"

#include "Global.h"
MSQLConnect WorkMSQL::msql_connect;

void WorkMSQL::Init(const MSQL_init_data &msql_init_data){
		
	msql_connect.Init(msql_init_data);
	
}


	
	


string WorkMSQL::Login(string login, string pass){

	MYSQL_RES *resul = msql_connect.Query("SELECT `id`, `pass` FROM  `users` WHERE login = '" + login + "' LIMIT 1");
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(resul)) != NULL) {
		if (row[1] == pass){
			
			return "OK|" + string(row[0]) + "|";
		}
		else{
			return "WrongPass";
		}
	}
	else{
		return "WrongLogin";
	}
	return "NULL";
}

string WorkMSQL::Registrate(string login, string pass){
	MYSQL_RES *resul = msql_connect.Query("SELECT `id` FROM  `users` WHERE login = '" + login + "' LIMIT 1");
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(resul)) != NULL) {
		return "LoginExist";
	}
	else{
		msql_connect.Query("INSERT INTO `users`(`login`, `pass`) VALUES('" + login + "', '" + pass + "')");
		
		return "RegistrateOK";
	}
	return "NULL";
}

string WorkMSQL::NeedPers(int num){
	MYSQL_RES *resul =  msql_connect.Query("SELECT `id`, `name`,`race` FROM  `pers` WHERE accId = '" + to_string(num) + "' LIMIT 5");
	MYSQL_ROW row;
	
	int indexK = 0;
	string temS;
	while ((row = mysql_fetch_row(resul)) != NULL){
		indexK++;
		temS += string(row[0]) + "|" + string(row[1]) + "|" + string(row[2]) + "|";
	}
	
	return  "Pers|" + to_string(indexK) + "|" + temS;
}

string WorkMSQL::CreatePers(const int &accNum,const string &name, const Person &pers){
	string ss = name;
	MYSQL_RES *resul = msql_connect.Query("SELECT `id` FROM  `pers` WHERE name = '" + name + "' LIMIT 1");
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		return "NameExist|";
	}
	else{
		msql_connect.Query("INSERT INTO `pers`( `accId`,`name`, `race`, `curHP`, `curMP`) VALUES('" 
			+ to_string(accNum) + "','" + name + "', '" + to_string(pers.GetRace()) + "','" + to_string(pers.GetCurHp())
			+ "','" + to_string(pers.GetCurMp()) + "')");
		MYSQL_RES *resul = msql_connect.Query("SELECT `id` FROM  `pers` WHERE name = '" + name + "' LIMIT 1");
		MYSQL_ROW row;
		if ((row = mysql_fetch_row(resul)) != NULL){
			string s = row[0];
			msql_connect.Query("INSERT INTO `inventory`( `persId`) VALUES('" + s + "')");
			msql_connect.Query("INSERT INTO `buff`( `persId`) VALUES('" + s + "')");
			msql_connect.Query("INSERT INTO `debuff`( `persId`) VALUES('" + s + "')");
		}
		return "CreatePersOK|";
	}
	
	return "NULL";
}

Person WorkMSQL::GamePerson(int num){
	Person pers = Person();
	MYSQL_RES *resul = msql_connect.Query("SELECT * FROM  `pers` WHERE id = '" + to_string(num) + "' LIMIT 1");
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		int it = 0;
		pers.SetPersId(atoi(row[it++]));
		it++;
		pers.SetName(row[it++]);
		pers.SetRace(atoi(row[it++]));
		pers.SetPosition(Vector3(atof(row[it++]), atof(row[it++]), atof(row[it++])));
		pers.SetRotation(atof(row[it++]));
		pers.SetLive(atoi(row[it++]) != 0);
		pers.SetResInPlace(atoi(row[it++]) != 0);
		pers.SetCorpseSaveTime(atof(row[it++]));
		pers.SetCurHp(atof(row[it++]));
		pers.SetCurMp(atof(row[it++]));
		pers.SetBaseStrength(atoi(row[it++]));
		pers.SetBaseAgility(atoi(row[it++]));
		pers.SetBaseConstitution(atoi(row[it++]));
		pers.SetBaseIntelligence(atoi(row[it++]));
		pers.SetBaseWisdom(atoi(row[it++]));
		pers.SetFreeCharacteristics(atoi(row[it++]));
		pers.SetWeaponSlot(atoi(row[it++]));
		pers.SetBodySlot(atoi(row[it++]));
		pers.SetVisibleRange(atof(row[it++]));
		pers.SetCharacteristicPoint(atoi(row[it++]));
		pers.SetAbilityPoint(atoi(row[it++]));
		pers.SetSpellPoint(atoi(row[it++]));
	}
	resul = msql_connect.Query("SELECT * FROM  `inventory` WHERE persId = '" + to_string(num) + "' LIMIT 1");
	row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		int it = 1;		
		for (int i = 0; i < INVENTORY_SIZE; i++){
			pers.inventory.GetSlot(i).SetItem(atoi(row[it++]));
			pers.inventory.GetSlot(i).SetCount(atoi(row[it++]));
		}
	}

	resul = msql_connect.Query("SELECT * FROM  `buff` WHERE persId = '" + to_string(num) + "' LIMIT 1");
	row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		int it = 1;
		vector<Buff> buffList;
		for (int i = 0; i < BUFF_COUNT; i++){
			buffList.push_back(Buff(atoi(row[it++]), atoi(row[it++]), atof(row[it++])));
		}
		pers.buffList.Init(buffList);
	}
	resul = msql_connect.Query("SELECT * FROM  `debuff` WHERE persId = '" + to_string(num) + "' LIMIT 1");
	row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		int it = 1;
		vector<Buff> debuffList;
		for (int i = 0; i < DEBUFF_COUNT; i++){
			debuffList.push_back(Buff(atoi(row[it++]), atoi(row[it++]), atof(row[it++])));
		}
		pers.debuffList.Init(debuffList);
	}
	resul = msql_connect.Query("SELECT * FROM  `mastery` WHERE persId = '" + to_string(num) + "' LIMIT 1");
	row;
	if ((row = mysql_fetch_row(resul)) != NULL){
		
		for (int i = 0; i < MASTERY_COUNT; i++){
			pers.masteryList.GetMastery(i).AddExp(atoi(row[i+1]));
		}
	}

	resul = msql_connect.Query("SELECT * FROM  `spell` WHERE persId = '" + to_string(num) + "' LIMIT 1");
	row;
	if ((row = mysql_fetch_row(resul)) != NULL){

		for (int i = 0; i < SPELL_COUNT; i++){
			pers.spellList.GetSpell(i).SetLearn(atoi(row[i * 2 - 1]) != 0);
			pers.spellList.GetSpell(i).SetCooldown(atof(row[i * 2]));
		}
	}

	return pers;
}

vector<Item> WorkMSQL::GetBaseItem(){
	MYSQL_RES *resul = msql_connect.Query("SELECT * FROM  `baseitem` ");
	MYSQL_ROW row;
	vector<Item> itemList;
	while ((row = mysql_fetch_row(resul)) != NULL){
		Item item = Item();
		int it = 1;
		
		item.SetType(row[it++]);

		item.SetStack(atoi(row[it++]) != 0);
		item.SetWeight(atof(row[it++]));
		item.SetSubType(row[it++]);
		item.SetMinAttack(atoi(row[it++]));
		item.SetMaxAttack(atoi(row[it++]));
		item.SetRangeAttack(atof(row[it++]));
		item.SetAccuracy(atoi(row[it++]));
		item.SetAttackSpeed(atoi(row[it++]));
		item.SetCritChance(atoi(row[it++]));
		item.SetCritRate(atoi(row[it++]));
		item.SetSpeedPenalty(atoi(row[it++]));
		item.SetFailCastSpell(atoi(row[it++]));
		item.SetResSlash(atoi(row[it++]));
		item.SetResCrush(atoi(row[it++]));
		item.SetResPierce(atoi(row[it++]));
		item.SetEvasionPenalty(atoi(row[it++]));
		itemList.push_back(item);
	}
	mysql_free_result(resul);
	return itemList;
}


vector<SpellInfo> WorkMSQL::GetBaseSpell(){
	MYSQL_RES *resul = msql_connect.Query("SELECT * FROM  `basespell` ");
	MYSQL_ROW row;
	vector<SpellInfo> spellList;
	while ((row = mysql_fetch_row(resul)) != NULL){
		SpellInfo spell = SpellInfo();
		int it = 1;
		
		spell.SetType(atoi(row[it++]));
		spell.SetActive(atoi(row[it++]) != 0);
		spell.SetLearn(atoi(row[it++]) != 0);
		spell.SetTargetType(atoi(row[it++]));
		spell.SetAnimType(atoi(row[it++]));
		spell.SetManaCost(atoi(row[it++]));
		spell.SetCastTime(atof(row[it++]));
		spell.SetRange(atof(row[it++]));
		spell.SetCooldown(atof(row[it++]));
		spell.SetGoldCost(atoi(row[it++]));
		spell.SetAbilityPointCost(atoi(row[it++]));
		spell.SetSpellPointCost(atoi(row[it++]));
		spell.SetMasteryLvlNeed(0, atoi(row[it++]));
		spell.SetMasteryLvlNeed(1, atoi(row[it++]));
		spell.SetMasteryLvlNeed(2, atoi(row[it++]));
		spell.SetMasteryLvlNeed(3, atoi(row[it++]));
		spell.SetMasteryLvlNeed(4, atoi(row[it++]));
		spell.SetMasteryLvlNeed(5, atoi(row[it++]));
		spell.SetMasteryLvlNeed(6, atoi(row[it++]));
		spell.SetMasteryLvlNeed(7, atoi(row[it++]));
		spell.SetMasteryLvlNeed(8, atoi(row[it++]));
		spell.SetMasteryLvlNeed(9, atoi(row[it++]));
		spell.SetIntelligenceNeed(atoi(row[it++]));
		spellList.push_back(spell);
	}
	mysql_free_result(resul);
	return spellList;
}

vector<Person> WorkMSQL::GetBasePerson(){
	MYSQL_RES *resul = msql_connect.Query("SELECT * FROM  `basepers` ");
	MYSQL_ROW row, row2, row3;
	MYSQL_RES *resul2 = msql_connect.Query("SELECT * FROM  `basepersmastery` ");
	MYSQL_RES *resul3 = msql_connect.Query("SELECT * FROM  `basepersspell` ");
	vector<Person> personList;
	while ((row = mysql_fetch_row(resul)) != NULL){
		row2 = mysql_fetch_row(resul2);
		row3 = mysql_fetch_row(resul3);
		Person pers = Person();
		int it = 1;
		
		pers.SetName(row[it++]);
		pers.SetRace(atoi(row[it++]));
		pers.SetCurHp(atof(row[it++]));
		pers.SetCurMp(atof(row[it++]));
		pers.SetBaseStrength(atoi(row[it++]));
		pers.SetBaseAgility(atoi(row[it++]));
		pers.SetBaseConstitution(atoi(row[it++]));
		pers.SetBaseIntelligence(atoi(row[it++]));
		pers.SetBaseWisdom(atoi(row[it++]));
		pers.SetVisibleRange(atof(row[it++]));
		pers.SetWeaponSlot(atoi(row[it++]));
		pers.SetBodySlot(atoi(row[it++]));
		pers.SetFreeCharacteristics(atoi(row[it++]));

		for (int i = 0; i < 44; i++){
			pers.spellList.GetSpell(i).SetLearn(atoi(row3[i+1]) != 0);
		}

		for (int i = 0; i < 10; i++){
			pers.masteryList.GetMastery(i).SetLvl(atoi(row2[i+1]));			
		}

		

		personList.push_back(pers);
	}
	mysql_free_result(resul);
	mysql_free_result(resul2);
	mysql_free_result(resul3);
	return personList;
}
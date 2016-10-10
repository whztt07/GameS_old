#include "stdafx.h"

/*

void Mechanic::PersUPD(int j){//Pers нужен static baseItemHolder
	
	float minAttack = 1, maxAttack = 2, attackSpeed = 600, critChance = 5, critRate = 2, attackRange = 1, accuracy = 4,
		speedPenalty = 0, failCastSpell = 0, evasionPenalty = 20, resSlash = 0, resCrush = 0, resPierce = 0, regenHPMod = 1,
		regenMPMod = 1, regenHPBonus = 0, regenMPBonus = 0, speedBonus = 0, bonusAttack = 0, bonusAttackRange = 0, bonusAttackSpeed = 0,
		bonusInvisible = 0, bonusDetection = 0, bonusConcentration = 0, bonusIntelligence = 0, bonusStrength = 0, bonusAgility = 0;
		bool root = false;
	  
	if (var->personList[j].weaponSlot > -1){
		Item weap = var->baseItemList[var->personList[j].weaponSlot];
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
	var->personList[j].speed = 3 * (1 + ( speedBonus - speedPenalty) * 0.01);

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


	var->personList[j].needPersUPD = false;
}


int Mechanic::GetItemIndex(int j){ // drop item holder
	for (int i = 0; i < var->dropItemList.size(); i++){
		if (var->dropItemList[i].id == j){
			return i;
		}
	}
	return -1;
}


PersonStatus Mechanic::GetPersonStatus(int j){//personholder
	EnterCriticalSection(&var->varSection);
	PersonStatus ps = var->personList[j].status;
	LeaveCriticalSection(&var->varSection);
	return ps;
}
void Mechanic::UPDPersonStats(){//person holder
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		if (var->personList[i].needPersUPD){
			PersUPD(i);
		}
		if (var->personList[i].needWeightUPD){
			WeightUPD(i);
		}
	}
	LeaveCriticalSection(&var->varSection);
}


void Mechanic::UPDPersonList(){//person holder
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		if (!var->personList[i].active){
			if (clock() - var->personList[i].lastPersUPD > 10000){
				var->personList.erase(var->personList.begin() + i);
				i--;
			}
		}
	}
	LeaveCriticalSection(&var->varSection);
}

void Mechanic::StatsUP(int index){
	
	int str = var->personList[index].statsUpData.q1, agi = var->personList[index].statsUpData.q2, con = var->personList[index].statsUpData.q3,
		intel = var->personList[index].statsUpData.q4, wis = var->personList[index].statsUpData.q5;

	int free = var->personList[index].freeCharacteristics, _str = var->personList[index].base_strength,
		_agi = var->personList[index].base_agility, _con = var->personList[index].base_constitution,
		_intel = var->personList[index].base_intelligence, _wis = var->personList[index].base_wisdom;
	
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

	var->personList[index].freeCharacteristics = free;
	var->personList[index].base_strength = _str;
	var->personList[index].base_agility = _agi;
	var->personList[index].base_constitution = _con;
	var->personList[index].base_intelligence = _intel;
	var->personList[index].base_wisdom = _wis;
	var->personList[index].needPersUPD = true;
	var->personList[index].status = idle;
}


void Mechanic::UseItem(int j){
		
		if (var->personList[j].useItemSlotNumber < 0){
			if (var->personList[j].useItemSlotNumber == -1 && var->personList[j].weaponSlot != -1){
				int freeSlot = FreeInventorySlot(j);

				if (freeSlot == -1){

					var->personList[j].status = idle;
										
					return;
				}
				else{
					var->personList[j].inventory[freeSlot].item = var->personList[j].weaponSlot;
					var->personList[j].inventory[freeSlot].count = 1;
					var->personList[j].weaponSlot = -1;
					var->personList[j].needPersUPD = true;
				}
			}
			if (var->personList[j].useItemSlotNumber == -2 && var->personList[j].bodySlot != -1){
				int freeSlot = FreeInventorySlot(j);
				if (freeSlot == -1){

					var->personList[j].status = idle;
					
					return;
				}
				else{
					var->personList[j].inventory[freeSlot].item = var->personList[j].bodySlot;
					var->personList[j].inventory[freeSlot].count = 1;
					var->personList[j].bodySlot = -1;
					var->personList[j].needPersUPD = true;
				}
			}
		}
		else{
			if (var->personList[j].inventory[var->personList[j].useItemSlotNumber].item != -1){
				string type = var->baseItemList[var->personList[j].inventory[var->personList[j].useItemSlotNumber].item].type;
				if (type == "Weapon"){

					int item = var->personList[j].weaponSlot;
					var->personList[j].weaponSlot = var->personList[j].inventory[var->personList[j].useItemSlotNumber].item;
					var->personList[j].inventory[var->personList[j].useItemSlotNumber].item = -1;
					var->personList[j].inventory[var->personList[j].useItemSlotNumber].count = 0;
					var->personList[j].needPersUPD = true;
					if (item > -1){
						int freeSlot = FreeInventorySlot(j);

						var->personList[j].inventory[freeSlot].item = item;
						var->personList[j].inventory[freeSlot].count = 1;
					}
				}
				if (type == "Armor"){

					int item = var->personList[j].bodySlot;
					var->personList[j].bodySlot = var->personList[j].inventory[var->personList[j].useItemSlotNumber].item;
					var->personList[j].inventory[var->personList[j].useItemSlotNumber].item = -1;
					var->personList[j].inventory[var->personList[j].useItemSlotNumber].count = 0;
					var->personList[j].needPersUPD = true;
					if (item > -1){
						int freeSlot = FreeInventorySlot(j);

						var->personList[j].inventory[freeSlot].item = item;
						var->personList[j].inventory[freeSlot].count = 1;
					}

				}
				if (type == "Potion"){
					string subType = var->baseItemList[var->personList[j].inventory[var->personList[j].useItemSlotNumber].item].subType;
					TakeItem(j, var->personList[j].useItemSlotNumber);
					if (subType == "HP"){
						AddBuff(j, 300, 5);
						if (var->personList[j].curHP < var->personList[j].maxHP){
							var->personList[j].curHP += 50 * var->personList[j].recoveryHP / 100;
							if (var->personList[j].curHP > var->personList[j].maxHP){
								var->personList[j].curHP = var->personList[j].maxHP;
							}
						}
					}
					if (subType == "MP"){
						AddBuff(j, 301, 5);
						if (var->personList[j].curMP < var->personList[j].maxMP){
							var->personList[j].curMP += 50 * var->personList[j].recoveryMP / 100;
							if (var->personList[j].curMP > var->personList[j].maxMP){
								var->personList[j].curMP = var->personList[j].maxMP;
							}
						}
					}
				}
			}
		}
	
	var->personList[j].status = idle;
	
}


int Mechanic::FreeInventorySlot(int j){
	int freeSlot = -1;
	for (int i = 0; i < INVENTORYSLOTCOUNT; i++){
		if (var->personList[j].inventory[i].item == -1){
			freeSlot = i;
			break;
		}
	}
	return freeSlot;
}

int Mechanic::InventorySlot(int j, int item){
	int freeSlot = -1;
	int itemSlot = -1;
	for (int i = 0; i < INVENTORYSLOTCOUNT; i++){
		if (var->personList[j].inventory[i].item == -1){
			freeSlot = i;
		}
		else if (var->personList[j].inventory[i].item == item){
			itemSlot = i;
			break;
		}
	}
	if (itemSlot == -1){
		return freeSlot;
	}
	else{
		return itemSlot;
	}
}

void Mechanic::TakeItem(int j, int slot, int count){
	var->personList[j].inventory[slot].count -= count;
	var->personList[j].curWeight -= var->baseItemList[var->personList[j].inventory[slot].item].weight;
	if (var->personList[j].inventory[slot].count <= 0){
		var->personList[j].inventory[slot].item = -1;
	}
	var->personList[j].needWeightUPD = true;
}

void Mechanic::AddBuff(int j, int type, float time, int level){
	int freeSlot = -1, delSlot = -1;
	
	for (int i = 0; i < 10; i++){
		if (var->personList[j].buffs[i].type == -1 && freeSlot == -1){
			freeSlot = i;
		}
		if (var->personList[j].buffs[i].type != -1 && delSlot == -1 && !var->personList[j].buffs[i].spec){
			delSlot = i;
		}
		if (var->personList[j].buffs[i].type == type){
			if (var->personList[j].buffs[i].level <= level){
				var->personList[j].buffs[i].level = level;
				var->personList[j].buffs[i].time = time;
				var->personList[j].buffs[i].spec = false;
				var->personList[j].needPersUPD = true;
			}
			return;
		}
	}
	if (freeSlot != -1){
		var->personList[j].buffs[freeSlot].type = type;
		var->personList[j].buffs[freeSlot].level = level;
		var->personList[j].buffs[freeSlot].time = time;
		var->personList[j].needPersUPD = true;
		var->personList[j].buffs[freeSlot].spec = false;
		if (type >= 400){
			var->personList[j].buffs[freeSlot].spec = true;
		}
	}
	else{
		if (delSlot != -1){
			var->personList[j].buffs.erase(var->personList[j].buffs.begin() + delSlot);
			var->personList[j].buffs.push_back(Buff(type, level, time));
			var->personList[j].needPersUPD = true;
			var->personList[j].buffs.back().spec = false;
			if (type >= 400){
				var->personList[j].buffs.back().spec = true;
			}
		}
	}

}

void Mechanic::AddDebuff(int j, int type, float time, int level){
	int freeSlot = -1, delSlot = -1;
	for (int i = 0; i < 10; i++){
		if (var->personList[j].debuffs[i].type == -1 && freeSlot == -1){
			freeSlot = i;
		}
		if (var->personList[j].debuffs[i].type != -1 && delSlot == -1 && !var->personList[j].debuffs[i].spec){
			delSlot = i;
		}
		if (var->personList[j].debuffs[i].type == type){
			if (var->personList[j].debuffs[i].level <= level){
				var->personList[j].debuffs[i].level = level;
				var->personList[j].debuffs[i].time = time;
				var->personList[j].debuffs[i].spec = false;
				var->personList[j].needPersUPD = true;
			}
			return;
		}
	}
	if (freeSlot != -1){
		var->personList[j].debuffs[freeSlot].type = type;
		var->personList[j].debuffs[freeSlot].level = level;
		var->personList[j].debuffs[freeSlot].time = time;
		var->personList[j].needPersUPD = true;
		var->personList[j].debuffs[freeSlot].spec = false;
		if (type >= 400){
			var->personList[j].debuffs[freeSlot].spec = true;
		}
	}
	else{
		if (delSlot != -1){
			var->personList[j].debuffs.erase(var->personList[j].debuffs.begin() + delSlot);
			var->personList[j].debuffs.push_back(Buff(type, level, time));
			var->personList[j].needPersUPD = true;
			var->personList[j].debuffs.back().spec = false;
			if (type >= 400){
				var->personList[j].debuffs.back().spec = true;
			}
		}
	}

}


void Mechanic::Regen(){
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		if (var->personList[i].live){
			int dif = clock() - var->personList[i].lastPersRegen;
			int count = dif / 1000;
			var->personList[i].lastPersRegen += count * 1000;
			if (count > 0){
				float regen;
				if (var->personList[i].battle){
					regen = var->personList[i].regenHPInBattle;
				}
				else{
					regen = var->personList[i].regenHPOutBattle;
				}
				regen *= count;
				if (regen > 0 && var->personList[i].curHP < var->personList[i].maxHP){
					var->personList[i].curHP += regen;
					if (var->personList[i].curHP > var->personList[i].maxHP){
						var->personList[i].curHP = var->personList[i].maxHP;
					}
				}
				if (regen < 0 && var->personList[i].curHP > 1){
					var->personList[i].curHP += regen;
					if (var->personList[i].curHP < 1){
						var->personList[i].curHP = 1;
					}
				}

				if (var->personList[i].battle){
					regen = var->personList[i].regenMPInBattle;
				}
				else{
					regen = var->personList[i].regenMPOutBattle;
				}
				regen *= count;
				if (regen > 0 && var->personList[i].curMP < var->personList[i].maxMP){
					var->personList[i].curMP += regen;
					if (var->personList[i].curMP > var->personList[i].maxMP){
						var->personList[i].curMP = var->personList[i].maxMP;
					}
				}
				if (regen < 0 && var->personList[i].curMP > 1){
					var->personList[i].curMP += regen;
					if (var->personList[i].curMP < 1){
						var->personList[i].curMP = 1;
					}
				}
			}
		}
	}
	LeaveCriticalSection(&var->varSection);
}


void Mechanic::BuffUPD(){
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		float dTime = (float)(clock() - var->personList[i].lastBuffUPD) / 1000.0;
		var->personList[i].lastBuffUPD = clock();
		for (int j = 0; j < 10; j++){
			if (!var->personList[i].buffs[j].spec && var->personList[i].buffs[j].type != -1){
				var->personList[i].buffs[j].time -= dTime;
				if (var->personList[i].buffs[j].time <= 0){
					DeleteBuff(i, var->personList[i].buffs[j].type);
					j--;
				}
						
				
			}
		}
		for (int j = 0; j < 10; j++){
			if (!var->personList[i].debuffs[j].spec && var->personList[i].debuffs[j].type != -1){
				var->personList[i].debuffs[j].time -= dTime;
				
				if (var->personList[i].debuffs[j].time <= 0){
					DeleteDebuff(i, var->personList[i].debuffs[j].type);
					j--;
				}
			}
		}
	}
	LeaveCriticalSection(&var->varSection);
}

void Mechanic::DeleteBuff(int j, int type){
	
	var->personList[j].needPersUPD = true;
	for (int i = 0; i < 10; i++){
		if (var->personList[j].buffs[i].type == type){
			var->personList[j].buffs.erase(var->personList[j].buffs.begin() + i);
			var->personList[j].buffs.push_back(Buff());
		}
	}

}

void Mechanic::DeleteDebuff(int j, int type){
	var->personList[j].needPersUPD = true;
	for (int i = 0; i < 10; i++){
		if (var->personList[j].debuffs[i].type == type){
			var->personList[j].debuffs.erase(var->personList[j].debuffs.begin() + i);
			var->personList[j].debuffs.push_back(Buff());
		}
	}

}

void Mechanic::WeightUPD(int j){
	
	float cur = var->personList[j].curWeight * 100.0 / var->personList[j].maxWeight;
	DeleteBuff(j, 400);
	DeleteBuff(j, 401);
	DeleteBuff(j, 402);
	if (cur >= 60 && cur < 80){		
		AddBuff(j, 400, 0);
	}
	if (cur >= 80 && cur < 100){		
		AddBuff(j, 401, 0);
	}
	if (cur >= 100){		
		AddBuff(j, 402, 0);
	}
	
}


float Mechanic::LastMainUPD(int j){
	EnterCriticalSection(&var->varSection);
	float dTime = (float)(clock() - var->personList[j].lastMainUPD) / 1000.0;
	var->personList[j].lastMainUPD = clock();
	LeaveCriticalSection(&var->varSection);
	return dTime;
}


bool Mechanic::TargetAttackRange(int j){
	bool ok = false;
	EnterCriticalSection(&var->varSection);
	string s = to_string(var->personList[j].status);
	if (Vector3::Distance(var->personList[j].position, var->personList[GetIndex(var->personList[j].targetNumber)].position)
		<= var->personList[j].attackRange){
		ok = true;
	}

	LeaveCriticalSection(&var->varSection);
	return ok;
}

bool Mechanic::PickupItemRange(int j){
	bool ok = false;
	EnterCriticalSection(&var->varSection);
	
	if (Vector3::Distance(var->personList[j].position, var->dropItemList[GetItemIndex(var->personList[j].pickupNumber)].position)
		<= 0.2){
		ok = true;
	}

	LeaveCriticalSection(&var->varSection);
	return ok;
}

void Mechanic::Attack(int j){
	
	
	if (!var->personList[j].does){
		int target = GetIndex(var->personList[j].targetNumber);
		if (var->personList[target].live){
			var->personList[j].attackTime = 750.0 / var->personList[j].attackSpeed;
			var->personList[j].does = true;
			var->personList[j].lastAttackTime = clock();
						
		}
		else{
			var->personList[j].status = idle;
			var->personList[j].targetNumber = -1;
		}
	}
	else{
		float time = (float)(clock() - var->personList[j].lastAttackTime) / 1000.0;
		if ( time >= var->personList[j].attackTime){
			var->personList[j].status = r_attack;
			int target = GetIndex(var->personList[j].targetNumber);
			if (var->personList[target].live){
				if (Random(1, 20) + var->personList[j].accuracy >= var->personList[target].evasion){
					var->personList[j].battle = true;
					var->personList[j].battleTime = clock();
					var->personList[target].battle = true;
					var->personList[target].battleTime = clock();
					AddTarget(target, var->personList[j].persID);
					int mod = 1;
					if (Random(0, 100) <= var->personList[j].critChance)
						mod = var->personList[j].critRate;
					float damage = Random(var->personList[j].minAttack, var->personList[j].maxAttack) * mod;
					damage -= var->personList[target].resistanceCrush;
					if (damage > 0)
						var->personList[target].curHP -= damage;
					if (var->personList[target].curHP <= 0 && var->personList[target].live){
						var->personList[target].curHP = 0;
						Kill(j, target);
					}
				}
				var->personList[j].does = false;
				if (var->personList[j].wait){
					var->personList[j].wait = false;
					var->personList[j].status = idle;
					var->personList[j].command = var->personList[j].waitingCommand;
					var->personList[j].data = var->personList[j].waitData;
				}
			}
			else{
				var->personList[j].status = idle;
			}
		}
	}


}

int Mechanic::Random(int min, int max){

	return (rand() % (max - min + 1)) + min;
}

float Mechanic::Randomf(int min, int max){

	return (rand() % ((max - min)*100 + 1)) / 100.0 + min;
}

void Mechanic::BattleStatusUPD(){
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		if (var->personList[i].battle){
			if (clock() - var->personList[i].battleTime > 10000){
				var->personList[i].battle = false;
			}
		}
		
	}
	LeaveCriticalSection(&var->varSection);
}


void Mechanic::Kill(int j, int target){

	
	var->personList[j].status = idle;
	var->personList[target].status = dead;
	var->personList[target].live = false;
	var->personList[target].corpseSaveTime = 15000;
	var->personList[target].deadTime = clock();
	var->personList[target].does = false;

	if (var->personList[target].persType == 2){
		for (int i = 0; i < var->personList[target].dropList.size(); i++){
			if (Random(0, 100) <= var->personList[target].dropList[i].chance){
				int count = Random(var->personList[target].dropList[i].minCount, var->personList[target].dropList[i].maxCount);
				float offsetX = Randomf(-1, 1), offsetZ = Randomf(-1, 1);
				DropItems(var->personList[target].dropList[i].item, count, Vector3(var->personList[target].position.x + offsetX, var->personList[target].position.y, var->personList[target].position.z + offsetZ));
			}
		}
		if (Random(0, 100) <= var->personList[target].pointDrop.totalChance){
			int chance = Random(0, 100);
			int count = Random(var->personList[target].pointDrop.minCount, var->personList[target].pointDrop.maxCount);
			if (chance <= var->personList[target].pointDrop.chanceCharacteristics){
				AddPoints(j, count, 0, 0);
			}
			else if (chance <= var->personList[target].pointDrop.chanceAbility){
				AddPoints(j, 0, count, 0);
			}
			else{
				AddPoints(j, 0, 0, count);
			}
		}
	}

	if (var->personList[j].targetNumber == var->personList[target].persID){
		var->personList[j].targetNumber = -1;
	}

}

void Mechanic::AddSpawnPoint(Vector3 pos, vector<int> vec, float time){
	EnterCriticalSection(&var->varSection);
	var->spawnPointList.push_back(SpawnPoint(pos, vec, time));
	LeaveCriticalSection(&var->varSection);
}

void Mechanic::SpawnPointUPD(){
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->spawnPointList.size(); i++){
		if (var->spawnPointList[i].curId != -1){
			if (!var->personList[GetIndex(var->spawnPointList[i].curId)].live){
				var->spawnPointList[i].curId = -1;
				var->spawnPointList[i].deadTime = clock();
			}
		}
		else{
			if (clock() - var->spawnPointList[i].deadTime >= var->spawnPointList[i].respawnTime){
				int rand = Random(0, var->spawnPointList[i].idList.size() - 1);
				AddPersonSave(var->basePersonList[var->spawnPointList[i].idList[rand]], 2);
				
				int num = var->NPCNumber--;
				int j = var->personList.size() - 1;
				var->personList[j].persID = num;
				var->spawnPointList[i].curId = num;
				float range = var->spawnPointList[i].spawnRange;
				float offsetX = Randomf(-1 * range, range), offsetZ = Randomf(-1 * range, range);
				var->personList[j].position = Vector3(var->spawnPointList[i].spawnPosition.x + offsetX,
					var->spawnPointList[i].spawnPosition.y, var->spawnPointList[i].spawnPosition.z + offsetZ);

			}
		}
	}
	LeaveCriticalSection(&var->varSection);
}

void Mechanic::AddPersonSave(Person pers, int type){
	
	var->personList.push_back(pers);
	int j = var->personList.size() - 1;
	var->personList[j].lastPersUPD = clock();
	var->personList[j].persType = type;
	for (int i = 0; i < INVENTORYSLOTCOUNT; i++){
		if (var->personList[j].inventory[i].item != -1){
			var->personList[j].curWeight += var->baseItemList[var->personList[j].inventory[i].item].weight * var->personList[j].inventory[i].count;
		}
	}
	var->personList[j].needWeightUPD = true;
	if (var->personList[j].needPersUPD){
		PersUPD(j);

	}
	
}


int Mechanic::GetSpawnPointSize(){
	EnterCriticalSection(&var->varSection);
	int count = var->spawnPointList.size();
	LeaveCriticalSection(&var->varSection);
	return count;
}

void Mechanic::DeadUPD(){

	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		if (!var->personList[i].live){
			if (clock() - var->personList[i].deadTime >= var->personList[i].corpseSaveTime){
				if (var->personList[i].persType == 2){
					var->personList.erase(var->personList.begin() + i);
				}
				else{
					var->personList[i].corpseSave = false;
					var->personList[i].resInPlace = false;
				}
			}
		}
	}
	LeaveCriticalSection(&var->varSection);

}

void Mechanic::AddTarget(int j, int num){
	if (var->personList[j].targetNumber == -1){
		var->personList[j].targetNumber = num;
	}
}

int Mechanic::GetTargetNumber(int j){
	EnterCriticalSection(&var->varSection);
	int targetNum = var->personList[j].targetNumber;
	LeaveCriticalSection(&var->varSection);
	return targetNum;
}

int Mechanic::GetPersonType(int j){
	EnterCriticalSection(&var->varSection);
	int n = var->personList[j].persType;
	LeaveCriticalSection(&var->varSection);
	return n;
}

bool Mechanic::GetPersonDoes(int j){
	EnterCriticalSection(&var->varSection);
	bool n = var->personList[j].does;
	LeaveCriticalSection(&var->varSection);
	return n;
}

void Mechanic::Resurrection(int j, bool place){
	EnterCriticalSection(&var->varSection);
	int num = GetIndex(j);
	Vector3 resPos = Vector3(1, 0, 1);
	if (!place)
		var->personList[num].position = resPos;
	
	var->personList[num].live = true;
	var->personList[num].curHP = var->personList[num].maxHP / 2.0;
	var->personList[num].status = idle;
	
	LeaveCriticalSection(&var->varSection);
}


void Mechanic::AddPoints(int j, int cha, int abi, int spe){
	var->personList[j].spellPoint += spe;
	var->personList[j].abilityPoint += abi;
	var->personList[j].characteristicPoint += cha;
}


void Mechanic::DropItems(int item, int count, Vector3 pos){
	int id = var->dropItemNumber++;
	var->dropItemList.push_back(DropItem(id, item, count, pos));
	
}

void Mechanic::Pickup(int j){
		
	int itemNum = GetItemIndex(var->personList[j].pickupNumber);
	if (itemNum != -1){
		if (AddItem(j, var->dropItemList[itemNum].item, var->dropItemList[itemNum].count)){
			var->dropItemList.erase(var->dropItemList.begin() + itemNum);
		}
	}
	var->personList[j].status = idle;
	
	
}

bool Mechanic::AddItem(int j, int item, int count){
	
	int freeSlot = InventorySlot(j, item);
	bool ok = false;
	if (freeSlot != -1){
		ok = true;
		var->personList[j].inventory[freeSlot].item = item;
		var->personList[j].inventory[freeSlot].count += count;
	}
	return ok;
}


void Mechanic::Command(string command, int id, Data data, bool b){
	EnterCriticalSection(&var->varSection);
	int index = GetIndex(id);
	if (b){
		if (var->personList[index].does){
			var->personList[index].wait = true;
			var->personList[index].waitingCommand = command;
			var->personList[index].waitData = data;			
		}
		else{
			var->personList[index].data = data;
			var->personList[index].command = command;			
		}
	}
	else{
		var->personList[index].dopCommand = command;
		var->personList[index].dopData = data;		
	}
	LeaveCriticalSection(&var->varSection);
}


string Mechanic::NeedUPD(int id){
	EnterCriticalSection(&var->varSection);
	int index = GetIndex(id);
	string s_UPD = var->personList[index].UPD;
	if (s_UPD == "NULL"){
		var->personList[index].needUPD = true;
	}
	var->personList[index].UPD = "NULL";
	LeaveCriticalSection(&var->varSection);
	return s_UPD;
	
}

string Mechanic::NeedUI_UPD(int id){
	EnterCriticalSection(&var->varSection);
	int index = GetIndex(id);
	string s_UPD = var->personList[index].UI_UPD;
	LeaveCriticalSection(&var->varSection);
	return s_UPD;
	
}


void Mechanic::UPDAnimation(){
	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){
		var->personList[i].animSpeed = 1.0;
		switch (var->personList[i].status){
		case idle:	
			if (var->personList[i].battle){
				var->personList[i].animStatus = animWarIdle;
			}
			else{
				var->personList[i].animStatus = animIdle;
			}
			break;
		case r_attack:
		case r_move:
		case r_pickup:
			if (var->personList[i].dvig && !var->personList[i].root && !var->personList[i].stan){
				if (var->personList[i].speed > 1.5){
					var->personList[i].animStatus = animRun;
					var->personList[i].animSpeed = var->personList[i].speed / 3.0;
				}
				else{
					var->personList[i].animStatus = animWalk;
					var->personList[i].animSpeed = var->personList[i].speed / 1.5;
				}
			}
			else{
				if (var->personList[i].battle){
					var->personList[i].animStatus = animWarIdle;
				}
				else{
					var->personList[i].animStatus = animIdle;
				}
			}
			break;

		case _move:
		case move_attack:
		case move_pickup:
			if (var->personList[i].root || var->personList[i].stan){
				if (var->personList[i].battle){
					var->personList[i].animStatus = animWarIdle;
				}
				else{
					var->personList[i].animStatus = animIdle;
				}
			}
			else{
				if (var->personList[i].speed > 1.5){
					var->personList[i].animStatus = animRun;
					var->personList[i].animSpeed = var->personList[i].speed / 3.0;
				}
				else{
					var->personList[i].animStatus = animWalk;
					var->personList[i].animSpeed = var->personList[i].speed / 1.5;
				}
			}
			break;

		case attack:
			if (var->baseItemList[var->personList[i].weaponSlot].subType == "Bow"){
				var->personList[i].animStatus = animRangeAttack;
			}
			else{
				var->personList[i].animStatus = animAttack;
			}
			var->personList[i].animSpeed = 1.0 / var->personList[i].attackTime;
			break;

		case dead:
			
			var->personList[i].animStatus = animDead;
			
			break;
		}
	}
	LeaveCriticalSection(&var->varSection);
}

void Mechanic::UPDPersonCommand(){


	EnterCriticalSection(&var->varSection);
	for (int i = 0; i < var->personList.size(); i++){

		if (var->personList[i].command == "Move"){
			var->personList[i].command = "";
			var->personList[i].status = r_move;
			Data dat = var->personList[i].data;
			Vector3 pos = Vector3(dat.q1, dat.q2, dat.q3);
			var->personList[i].movePosition = pos;
			var->personList[i].needPathUPD = true;
		}
		if (var->personList[i].command == "Attack"){
			var->personList[i].command = "";
			var->personList[i].status = r_attack;
			Data dat = var->personList[i].data;
			var->personList[i].targetNumber = dat.q1;

		}
		if (var->personList[i].command == "Cast"){
			var->personList[i].command = "";


		}
		if (var->personList[i].command == "UseItem"){
			var->personList[i].command = "";
			var->personList[i].status = useItem;
			Data dat = var->personList[i].data;
			var->personList[i].useItemSlotNumber = dat.q1;
		}
		if (var->personList[i].command == "Pickup"){
			var->personList[i].command = "";
			var->personList[i].status = r_pickup;
			Data dat = var->personList[i].data;
			var->personList[i].pickupNumber = dat.q1;
		}
		if (var->personList[i].command == "Resurrection"){
			var->personList[i].command = "";
			var->personList[i].status = res;
		}
		if (var->personList[i].command == "ResurrectionInPlace"){
			var->personList[i].command = "";
			var->personList[i].status = resplace;
		}
		if (var->personList[i].command == "DropItem"){
			var->personList[i].command = "";

		}
		if (var->personList[i].command == "Dialog"){
			var->personList[i].command = "";

		}
		if (var->personList[i].command == "StatsUP"){
			var->personList[i].command = "";
			var->personList[i].status = statsUp;
			var->personList[i].statsUpData = var->personList[i].data;
		}

	}
	LeaveCriticalSection(&var->varSection);

}

void Mechanic::UPDAction(){
	EnterCriticalSection(&var->varSection);
	int n = var->personList.size();
	for (int i = 0; i < n; i++){
		
		float dsTime = (float)(clock() - var->personList[i].lastMainUPD) / 1000.0;
		var->personList[i].lastMainUPD = clock();
		
		float dlTime = 0;
		while (dsTime > 0){

			if (dsTime > 0.025){
				dlTime = 0.025;
				dsTime -= 0.025;
			}
			else{
				dlTime = dsTime;
				dsTime = 0;
			}
			if (GeoDvig::FallingPerson(dlTime, i)){
				Vector3 targPos;
				int itemIndex;
				switch (var->personList[i].status){
				case r_move:
					if (var->personList[i].needPathUPD){
						GeoDvig::NeedPersonPath(i, var->personList[i].movePosition);
						var->personList[i].needPathUPD = false;
						var->personList[i].dvig = false;
					}
					else{
						GeoDvig::MoveRotation(dlTime, i);
					}
					break;
				case _move:
					var->personList[i].dvig = true;
					GeoDvig::MovePerson(dlTime, i);
					break;
				case r_attack:
					targPos = var->personList[GetIndex(var->personList[i].targetNumber)].position;
					if (Vector3::Distance(var->personList[i].position, targPos) <= var->personList[i].attackRange){
						GeoDvig::TargetRotation(dlTime, i);
					}
					else{
						if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.5){
							GeoDvig::NeedPersonPath(i, targPos);
							var->personList[i].dvig = false;
						}
						GeoDvig::MoveRotation(dlTime, i);
					}
					break;
				case move_attack:

					targPos = var->personList[GetIndex(var->personList[i].targetNumber)].position;
					if (Vector3::Distance(var->personList[i].position, targPos) <= var->personList[i].attackRange){
						var->personList[i].status = r_attack;
					}
					else{
						if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.5){
							GeoDvig::NeedPersonPath(i, targPos);
							var->personList[i].status = r_attack;
						}
						else{
							var->personList[i].dvig = true;
							GeoDvig::MovePerson(dlTime, i);
						}
					}
					break;
				case attack:

					GeoDvig::TargetDoesRotation(dlTime, i);
					Attack(i);
					break;
				case r_pickup:
					itemIndex = GetItemIndex(var->personList[i].pickupNumber);
					if (itemIndex == -1){
						var->personList[i].status = idle;
					}
					else{
						targPos = var->dropItemList[itemIndex].position;
						if (Vector3::Distance(var->personList[i].position, targPos) <= 0.2){
							GeoDvig::TargetItemRotation(dlTime, i);
						}
						else{
							if (var->personList[i].pathList.size() == 0 || Vector3::Distance(targPos, var->personList[i].pathList.back()) > 0.2){
								GeoDvig::NeedPersonPath(i, targPos);
								var->personList[i].dvig = false;
							}
							GeoDvig::MoveRotation(dlTime, i);
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
							GeoDvig::MovePerson(dlTime, i);
						}
					}
					break;
				case pickup:
					Pickup(i);
					break;
				case statsUp:
										
					StatsUP(i);
					break;
				case useItem:

					UseItem(i);
					break;
				}
			}
			else{
				switch (var->personList[i].status){
				
				case _move:
					var->personList[i].status = r_move;
					break;
				case move_attack:
					var->personList[i].status = r_attack;
					break;
				case move_pickup:
					var->personList[i].status = r_pickup;
					break;
				default: var->personList[i].status = idle;
					break;
				}
			}
		}
		/*
		if (status == pickup){
			float dsTime = dTime;
			float dlTime = 0;
			while (dsTime > 0){

				if (dsTime > 0.025){
					dlTime = 0.025;
					dsTime -= 0.025;
				}
				else{
					dlTime = dsTime;
					dsTime = 0;
				}
				if (Mechanic::GetPersonStatus(i) == pickup){
					if (Mechanic::PickupItemRange(i)) {
						if (GeoDvig::TargetItemRotation(dlTime, i)){
							Mechanic::Pickup(i);
						}
					}
					else{
						GeoDvig::MovePerson(dlTime, i);
					}
				}
			}
		}
	}
	LeaveCriticalSection(&var->varSection);
}




void Mechanic::UPDGameClientsData(){
	string ss = ""; 
	EnterCriticalSection(&var->varSection);
	int countPerson = var->personList.size();
	for (int i = 0; i < countPerson; i++){
		if (var->personList[i].needUPD){


			var->personList[i].lastPersUPD = clock();
			ss = "AllUPD|" + to_string(var->personList[i].persID) + "|" + var->personList[i].name + "|"
				+ to_string(var->personList[i].live) + "|" + to_string(var->personList[i].corpseSave) + "|"
				+ to_string(var->personList[i].resInPlace) + "|" + to_string(var->personList[i].position.x) + "|"
				+ to_string(var->personList[i].position.y) + "|" + to_string(var->personList[i].position.z) + "|"
				+ to_string(var->personList[i].rotation.y) + "|" + to_string(var->personList[i].curHP) + "|"
				+ to_string(var->personList[i].maxHP) + "|" + to_string(var->personList[i].curMP) + "|"
				+ to_string(var->personList[i].maxMP) + "|" + to_string(var->personList[i].animStatus) + "|"
				+ to_string(var->personList[i].animSpeed) + "|" + to_string(var->personList[i].targetNumber) + "|";
			string dopcurstring = "";
			int iternum = 0;
			for (int j = 0; j < var->personList.size(); j++){
				if (j != i && Vector3::Distance(var->personList[j].position, var->personList[i].position) <= var->personList[i].visibleRange){
					iternum++;
					dopcurstring += to_string(var->personList[j].persID) + "|" + var->personList[j].name + "|"
						+ to_string(var->personList[j].live) + "|" + to_string(var->personList[j].position.x) + "|"
						+ to_string(var->personList[j].position.y) + "|" + to_string(var->personList[j].position.z) + "|"
						+ to_string(var->personList[j].rotation.y) + "|"
						+ to_string(var->personList[j].curHP / var->personList[j].maxHP) + "|" + to_string(var->personList[j].animStatus) + "|"
						+ to_string(var->personList[j].animSpeed) + "|";

				}
			}
			ss += to_string(iternum) + "|";
			ss += dopcurstring;

			dopcurstring = "";
			iternum = 0;
			for (int j = 0; j < var->dropItemList.size(); j++){
				if (Vector3::Distance(var->dropItemList[j].position, var->personList[i].position) <= var->personList[i].visibleRange){
					iternum++;
					dopcurstring += to_string(var->dropItemList[j].id) + "|" + to_string(var->dropItemList[j].position.x) + "|"
						+ to_string(var->dropItemList[j].position.y) + "|" + to_string(var->dropItemList[j].position.z) + "|";
				}
			}
			ss += to_string(iternum) + "|";
			ss += dopcurstring;
			var->personList[i].UPD = ss;

			ss = "";

			var->personList[i].lastPersUPD = clock();
			ss = "UIUPD|" + to_string(var->personList[i].base_strength) + "|" + to_string(var->personList[i].base_agility) + "|"
				+ to_string(var->personList[i].base_constitution) + "|" + to_string(var->personList[i].base_intelligence) + "|"
				+ to_string(var->personList[i].base_wisdom) + "|"
				+ to_string(var->personList[i].strength) + "|" + to_string(var->personList[i].agility) + "|"
				+ to_string(var->personList[i].constitution) + "|" + to_string(var->personList[i].intelligence) + "|"
				+ to_string(var->personList[i].wisdom) + "|" + to_string(var->personList[i].modStrength) + "|"
				+ to_string(var->personList[i].modAgility) + "|" + to_string(var->personList[i].modConstitution) + "|"
				+ to_string(var->personList[i].modIntelligence) + "|" + to_string(var->personList[i].modWisdom) + "|"
				+ to_string(var->personList[i].minAttack) + "|" + to_string(var->personList[i].maxAttack) + "|"
				+ to_string(var->personList[i].attackSpeed) + "|" + to_string(var->personList[i].critChance) + "|"
				+ to_string(var->personList[i].critRate) + "|" + to_string(var->personList[i].evasion) + "|"
				+ to_string(var->personList[i].accuracy) + "|" + to_string(var->personList[i].speed) + "|"
				+ to_string(var->personList[i].saveReaction) + "|" + to_string(var->personList[i].savePersistence) + "|"
				+ to_string(var->personList[i].saveWill) + "|" + to_string(var->personList[i].saveDeath) + "|"
				+ to_string(var->personList[i].complexitySpell) + "|" + to_string(var->personList[i].complexityAbility) + "|"
				+ to_string(var->personList[i].invisible) + "|" + to_string(var->personList[i].detection) + "|"
				+ to_string(var->personList[i].concentration) + "|" + to_string(var->personList[i].failSpellChance) + "|"
				+ to_string(var->personList[i].rotationSpeed) + "|" + to_string(var->personList[i].visibleRange) + "|"
				+ to_string(var->personList[i].attackRange) + "|" + to_string(var->personList[i].recoveryHP) + "|"
				+ to_string(var->personList[i].recoveryMP) + "|" + to_string(var->personList[i].regenHPOutBattle) + "|"
				+ to_string(var->personList[i].regenMPOutBattle) + "|" + to_string(var->personList[i].regenHPInBattle) + "|"
				+ to_string(var->personList[i].regenMPInBattle) + "|" + to_string(var->personList[i].resistanceSlash) + "|"
				+ to_string(var->personList[i].resistanceCrush) + "|" + to_string(var->personList[i].resistancePierce) + "|"
				+ to_string(var->personList[i].resistanceFire) + "|" + to_string(var->personList[i].resistanceCold) + "|"
				+ to_string(var->personList[i].resistanceNegative) + "|" + to_string(var->personList[i].freeCharacteristics) + "|"
				+ to_string(var->personList[i].curWeight) + "|" + to_string(var->personList[i].maxWeight) + "|"
				+ to_string(var->personList[i].characteristicPoint) + "|" + to_string(var->personList[i].abilityPoint) + "|"
				+ to_string(var->personList[i].spellPoint) + "|" + to_string(var->personList[i].weaponSlot) + "|"
				+ to_string(var->personList[i].bodySlot) + "|";

			for (int j = 0; j < INVENTORYSLOTCOUNT; j++){
				ss += to_string(var->personList[i].inventory[j].item) + "|" + to_string(var->personList[i].inventory[j].count) + "|";
			}
			for (int j = 0; j < 10; j++){
				ss += to_string(var->personList[i].buffs[j].type) + "|";
			}
			for (int j = 0; j < 10; j++){
				ss += to_string(var->personList[i].debuffs[j].type) + "|";
			}
			for (int j = 0; j < 10; j++){
				ss += to_string(var->personList[i].masteryList[j].curLvl) + "|";
				float f;
				if (var->personList[i].masteryList[j].curLvl > 0){
					f = (var->personList[i].masteryList[j].curExp -
						var->personList[i].masteryList[j].lvlExp[var->personList[i].masteryList[j].curLvl]) / 
						var->personList[i].masteryList[j].lvlExp[var->personList[i].masteryList[j].curLvl + 1];
				}
				else{
					f = var->personList[i].masteryList[j].curExp /
						var->personList[i].masteryList[j].lvlExp[var->personList[i].masteryList[j].curLvl + 1];
				}
				ss += to_string(f) + "|";
			}
			int num = 0;
			dopcurstring = "";
			for (int j = 0; j < 20; j++){
				if (var->personList[i].spellList[j].learn){
					num++;
					dopcurstring += to_string(j) + "|" + to_string(var->personList[i].spellList[j].lvl) + "|"
						+ to_string(var->personList[i].spellList[j].cooldown / var->baseSpellList[j].cooldown) + "|";
				}
					
			}
			ss += to_string(num) + "|" + dopcurstring;
			num = 0;
			dopcurstring = "";
			for (int j = 20; j < 44; j++){
				if (var->personList[i].spellList[j].learn){
					num++;
					dopcurstring += to_string(j) + "|" + to_string(var->personList[i].spellList[j].lvl) + "|"
						+ to_string(var->personList[i].spellList[j].cooldown / var->baseSpellList[j].cooldown) + "|";
				}

			}
			ss += to_string(num) + "|" + dopcurstring;
			var->personList[i].UI_UPD = ss;
			var->personList[i].needUPD = false;
			

		}
	}
	LeaveCriticalSection(&var->varSection);
}*/
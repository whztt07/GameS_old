#include "stdafx.h"

/*

int Mechanic::GetItemIndex(int j){ // drop item holder
	for (int i = 0; i < var->dropItemList.size(); i++){
		if (var->dropItemList[i].id == j){
			return i;
		}
	}
	return -1;
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
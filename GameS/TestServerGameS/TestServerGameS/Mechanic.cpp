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
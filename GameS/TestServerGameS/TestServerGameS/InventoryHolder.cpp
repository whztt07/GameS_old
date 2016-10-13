#include "stdafx.h"

#include <vector>

#include "InventoryHolder.h"
#include "Global.h"
using namespace std;


InventoryHolder::InventoryHolder(int slotCount){
	for (int i = 0; i < slotCount; i++){
		inventory.push_back(InventorySlot());
	}
}

InventorySlot& InventoryHolder::GetSlot(int index){
	return inventory[index];
}

int InventoryHolder::FreeInventorySlot() const{
	int freeSlot = -1;
	for (int i = 0; i < INVENTORY_SIZE; i++){
		if (inventory[i].GetItemId() == -1){
			freeSlot = i;
			break;
		}
	}
	return freeSlot;
}

void InventoryHolder::TakeItem(int slot, int count){
	inventory[slot].TakeCount(count);
	
	if (inventory[slot].GetCount() <= 0){
		inventory[slot].SetItemId(-1);
	}	
}


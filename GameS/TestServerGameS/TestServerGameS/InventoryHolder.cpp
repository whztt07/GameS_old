#include "stdafx.h"

#include <vector>

#include "InventoryHolder.h"

using namespace std;


InventoryHolder::InventoryHolder(int slotCount){
	for (int i = 0; i < slotCount; i++){
		inventory.push_back(InventorySlot());
	}
}

InventorySlot& InventoryHolder::GetSlot(int index){
	return inventory[index];
}
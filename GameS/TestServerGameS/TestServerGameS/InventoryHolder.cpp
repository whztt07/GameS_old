#include "stdafx.h"

#include <vector>

#include "InventoryHolder.h"

using namespace std;


InventoryHolder::InventoryHolder(const int &count){
	for (int i = 0; i < count; i++){
		inventory.push_back(InventorySlot());
	}
}

InventorySlot& InventoryHolder::GetSlot(const int &i){
	return inventory[i];
}
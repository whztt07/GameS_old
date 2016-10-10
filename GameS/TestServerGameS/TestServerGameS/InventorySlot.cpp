#include "stdafx.h"

#include "InventorySlot.h"

InventorySlot::InventorySlot() : itemId(-1), count(){}

void InventorySlot::SetItemId(int newItemId){
	itemId = newItemId;
}

void InventorySlot::SetCount(int newCount){
	count = newCount;
}

#include "stdafx.h"

#include "InventorySlot.h"

InventorySlot::InventorySlot() : itemId(-1), count(){}

void InventorySlot::SetItemId(int newItemId){
	itemId = newItemId;
}

void InventorySlot::SetCount(int newCount){
	count = newCount;
}

const int& InventorySlot::GetItemId() const{
	return itemId;
}

const int& InventorySlot::GetCount() const{
	return count;
}
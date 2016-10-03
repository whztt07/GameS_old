#include "stdafx.h"

#include "InventorySlot.h"

InventorySlot::InventorySlot() : item(-1), count(){}

void InventorySlot::SetItem(const int &_item){
	item = _item;
}

void InventorySlot::SetCount(const int &_count){
	count = _count;
}

const int& InventorySlot::GetItem() const{
	return item;
}

const int& InventorySlot::GetCount() const{
	return count;
}
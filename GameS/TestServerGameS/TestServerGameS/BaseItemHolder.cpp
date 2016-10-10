#include "stdafx.h"

#include <vector>

#include "Item.h"
#include "BaseItemHolder.h"


void BaseItemHolder::Init(const vector<Item> &newItemList){
	itemList = newItemList;
}

const Item& BaseItemHolder::GetItem(int index) const{
	return itemList[index];
}
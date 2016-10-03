#include "stdafx.h"

#include <vector>

#include "Item.h"
#include "BaseItemHolder.h"


void BaseItemHolder::Init(const vector<Item> &vec){
	itemList = vec;
}



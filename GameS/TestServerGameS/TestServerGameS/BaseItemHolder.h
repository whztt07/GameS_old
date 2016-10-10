#pragma once


#include <vector>

#include "Item.h"


class BaseItemHolder{
	vector<Item> itemList;
public:
	void		Init(const vector<Item> &newItemList);
	const Item&	GetItem(int index) const;
};
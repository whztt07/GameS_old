#include "Vector3.h"

struct DropItem{
	
	DropItem(int _id, int _item, int _count, Vector3 pos): position(pos), item(_item), count(_count), id(_id){}
	Vector3 position;
	int item, id, count;
};
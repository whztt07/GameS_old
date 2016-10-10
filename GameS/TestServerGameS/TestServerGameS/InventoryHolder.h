
#include <vector>

#include "InventorySlot.h"

using namespace std;

class InventoryHolder{
	vector<InventorySlot> inventory;
public:
	InventoryHolder(int slotCount);

	InventorySlot& GetSlot(int index);
};
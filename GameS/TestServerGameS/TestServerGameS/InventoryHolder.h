
#include <vector>

#include "InventorySlot.h"

using namespace std;

class InventoryHolder{
	vector<InventorySlot> inventory;
public:
	InventoryHolder(int slotCount);

	InventorySlot&	GetSlot(int index);

	void			TakeItem(int slot, int count = 1);
	int				FreeInventorySlot() const;
};
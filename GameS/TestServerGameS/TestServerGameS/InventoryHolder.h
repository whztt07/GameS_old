
#include <vector>

#include "InventorySlot.h"

using namespace std;

class InventoryHolder{
	vector<InventorySlot> inventory;
public:
	InventoryHolder(const int&);
	InventorySlot& GetSlot(const int&);
};
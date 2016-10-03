


class InventorySlot{
	
	int item, count;	
public:
	InventorySlot();
	void SetItem(const int&);
	void SetCount(const int&);

	const int& GetItem() const;
	const int& GetCount() const;
};
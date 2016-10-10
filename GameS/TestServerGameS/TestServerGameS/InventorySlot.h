


class InventorySlot{
	
	int itemId;
	int count;
public:
	InventorySlot();

	void		SetItemId(int newItemId);
	void		SetCount(int newCount);

	const int&	GetItemId() const;
	const int&	GetCount() const;
};
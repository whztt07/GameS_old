

struct Drop{
	Drop(int _item, int _chance, int _min, int _max) : chance(_chance), item(_item), minCount(_min), maxCount(_max){}
	int chance, item, minCount, maxCount;	
};
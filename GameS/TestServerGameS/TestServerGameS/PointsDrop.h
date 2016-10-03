

struct PointsDrop{
	PointsDrop() : chanceCharacteristics(), chanceAbility(), chanceSpell(), minCount(), maxCount(), totalChance(){}
	PointsDrop(int _totalChance, int _chanceCharacteristics, int _chanceAbility, int _chanceSpell, int _min, int _max) 
		: chanceCharacteristics(_chanceCharacteristics), chanceAbility(_chanceAbility), chanceSpell(_chanceSpell), 
		minCount(_min), maxCount(_max), totalChance(_totalChance){}

	int chanceCharacteristics, chanceAbility, chanceSpell, minCount, maxCount, totalChance;

};
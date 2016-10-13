
#include <vector>

#include "Buff.h"

using namespace std;

class BuffHolder{
	vector<Buff> buffList;
public:
	BuffHolder(const int &buffCount);

	void		Init(const vector<Buff> &newBuffList);
	const Buff&	GetBuff(int index) const;
	void		AddBuff(int type, float time, int level = 1);
	void		DeleteBuff(int type);
	void		UpdateBuffs(float deltaTime);
};
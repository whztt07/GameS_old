
#include <vector>

#include "Buff.h"

using namespace std;

class BuffHolder{
	vector<Buff> buffList;
public:
	BuffHolder(const int &buffCount);

	void Init(const vector<Buff> &newBuffList);
};
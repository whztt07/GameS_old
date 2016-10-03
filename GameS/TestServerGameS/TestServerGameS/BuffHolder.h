
#include <vector>

#include "Buff.h"

using namespace std;

class BuffHolder{
	vector<Buff> buffList;
public:
	BuffHolder(const int&);
	void Init(const vector<Buff>&);
};
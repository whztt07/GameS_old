#include "stdafx.h"

#include "Buff.h"


Buff::Buff(int type, int level, float time, bool special) : type(type), level(level), time(time), special(special){}
Buff::Buff() : type(-1), level(1), time(), special(){}
#include "stdafx.h"

#include "Buff.h"


Buff::Buff(int _type, int _level, float _time, bool _spec) : type(_type), level(_level), time(_time), spec(_spec){}
Buff::Buff() : type(-1), level(1), time(), spec(){}
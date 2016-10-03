#pragma once
#include "GeoCell.h"


struct GeoCube {

	GeoCube() : type(), geoCells(){}
	GeoCube(int typ, GeoCell _cell[]) : type(typ){
		
		for (int i = 0; i < 64; i++){
			geoCells[i] = _cell[i];
		}
	}
	int type;
	GeoCell geoCells[64];
};
#include <vector>
#pragma once
#include "GeoCube.h"

class GeoData {
public:
	GeoData() : size_x(), size_z(){}
	GeoData(const GeoData &geo) : size_x(geo.size_x), size_z(geo.size_z), geoCubs(geo.geoCubs){}
	int size_x, size_z;
	std::vector<GeoCube> geoCubs;
	
};
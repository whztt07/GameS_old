#pragma once
#include <vector>

#include "GeoCube.h"

class Person;
class Vector3;

using namespace std;

class GeoData {
	
	int				size_x;
	int				size_z;
	vector<GeoCube>	geoCubs;

	float	GeoHeight(const Vector3 &position) const;
	float	GetAngle(const Vector3 &position) const;	
	float	GetRotation(float angle) const;
	
public:	
	GeoData();
	GeoData(const GeoData&);

	void SetSizeX(int newSizeX);
	void SetSizeZ(int newSizeZ);

	void AddGeoCub(const GeoCube &newGeoCub);
	bool FallingPerson(float deltaTime, Person &person) const;
	void MovePerson(float deltaTime, Person &person) const;
	void NeedPersonPath(Person &person, const Vector3 &movePosition) const;	
	bool Rotate(float deltaTime, Person &person, const Vector3 &position) const;
};

#pragma once



struct Vector3{
	float x, y, z;

	Vector3();
	Vector3(float _x, float _y, float _z);
	
	static const float Distance(const Vector3&, const Vector3&);
	const Vector3 operator- (const Vector3&) const;
	const Vector3 operator+ (const Vector3&) const;
	const Vector3& operator+= (const Vector3&);
	void Normalize();
	
};


const Vector3 operator* (const Vector3&, const float&);
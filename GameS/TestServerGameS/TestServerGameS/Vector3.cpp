
#include "stdafx.h"

#include "Vector3.h"

const Vector3 operator* (const Vector3& v, const float& n){
	return Vector3(v.x*n, v.y*n, v.z*n);
}

Vector3::Vector3() : x(), y(), z(){}
Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

const float Vector3::Distance(const Vector3 &vector1, const Vector3 &vector2){
	return sqrtf((vector2.x - vector1.x)*(vector2.x - vector1.x) + (vector2.y - vector1.y) * (vector2.y - vector1.y) + (vector2.z - vector1.z) * (vector2.z - vector1.z));
}
const Vector3 Vector3::operator- (const Vector3 &vector) const{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}
const Vector3 Vector3::operator+ (const Vector3 &vector) const{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

const Vector3& Vector3::operator+= (const Vector3 &vector){
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}
void Vector3::Normalize(){
	float dlin = sqrtf(x*x + y*y + z*z);
	x = x / dlin;
	y = y / dlin;
	z = z / dlin;
}
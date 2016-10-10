
#include "stdafx.h"

#include "Vector3.h"

const Vector3 operator* (const Vector3 &vector, float multiplier){
	return Vector3(vector.x*multiplier, vector.y*multiplier, vector.z*multiplier);
}

Vector3::Vector3() : x(), y(), z(){}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z){}

float Vector3::Distance(const Vector3 &vector1, const Vector3 &vector2){
	return sqrtf((vector2.x - vector1.x)*(vector2.x - vector1.x) + (vector2.y - vector1.y) * (vector2.y - vector1.y) + (vector2.z - vector1.z) * (vector2.z - vector1.z));
}
const Vector3 Vector3::operator- (const Vector3 &vector) const{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}
const Vector3 Vector3::operator+ (const Vector3 &vector) const{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3& Vector3::operator+= (const Vector3 &vector){
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}
void Vector3::Normalize(){
	float length = sqrtf(x*x + y*y + z*z);
	x = x / length;
	y = y / length;
	z = z / length;
}
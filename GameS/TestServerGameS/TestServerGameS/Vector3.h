
#pragma once



class Vector3{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	
	static	float		Distance(const Vector3 &vector1, const Vector3 &vector2);
			const Vector3	operator- (const Vector3 &vector) const;
			const Vector3	operator+ (const Vector3 &vector) const;
			Vector3&		operator+= (const Vector3 &vector);
			void			Normalize();
	
};


const Vector3 operator* (const Vector3 &vector, float multiplier);
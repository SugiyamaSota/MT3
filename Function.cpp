#include "Function.h"
#include"Struct.h"
#include"Vector.h"
#include<cmath>

bool isCollision(const Sphere& s1, const Sphere& s2) {
	float distance = Length(Subtract(s1.center, s2.center));
	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

bool isCollision(const Sphere& s, const Plane& p) {
	float distance = Dot(s.center, p.normal) - p.distance;
	distance = fabs(distance);
	if (distance <= s.radius) {
		return true;
	} else {
		return false;
	}
}

Vector3 Perpendicuar(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return{ 0.0f,-vector.z,vector.y };
}
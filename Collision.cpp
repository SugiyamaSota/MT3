#include "Collision.h"
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

bool isCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >=0.0f,t<=1.0f) {
		return true;
	} else {
		return false;
	}
}
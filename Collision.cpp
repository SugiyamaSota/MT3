#include "Collision.h"
#include"Struct.h"
#include"Vector.h"
#include<cmath>

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	float distance = Length(Subtract(s1.center, s2.center));
	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Sphere& s, const Plane& p) {
	float distance = Dot(s.center, p.normal) - p.distance;
	distance = fabs(distance);
	if (distance <= s.radius) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Plane trianglePlane;

	Vector3 v1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v2 = Subtract(triangle.vertices[2], triangle.vertices[0]);

	trianglePlane.normal = Normalize(Cross(v1, v2));
	trianglePlane.distance = Dot(trianglePlane.normal, triangle.vertices[0]);

	float dot = Dot(trianglePlane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (trianglePlane.distance - Dot(segment.origin, trianglePlane.normal)) / dot;

	if (t < 0.0f && t > 1.0f) {
		return false;
	}

	Vector3 p = Add(segment.origin, Multiply(t, segment.diff));

	Vector3 v[3];

	v[0] = Subtract(triangle.vertices[0], triangle.vertices[1]);
	v[1] = Subtract(triangle.vertices[1], triangle.vertices[2]);
	v[2] = Subtract(triangle.vertices[2], triangle.vertices[0]);


	Vector3 vp[3];
	vp[0] = Subtract(triangle.vertices[0], p);
	vp[1] = Subtract(triangle.vertices[1], p);
	vp[2] = Subtract(triangle.vertices[2], p);

	Vector3 cross[3];
	for (int i = 0; i < 3; i++) {
		cross[i] = Cross(v[i], vp[i]);
	}

	if (Dot(cross[0], trianglePlane.normal) >= 0.0f && Dot(cross[1], trianglePlane.normal) >= 0.0f && Dot(cross[2], trianglePlane.normal) >= 0.0f) {
		return true;
	} else {
		return false;
	}

}
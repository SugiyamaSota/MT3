#pragma once

struct Sphere;
struct Plane;
struct Vector3;

bool isCollision(const Sphere& s1, const Sphere& s2);

bool isCollision(const Sphere& s, const Plane& p);

Vector3 Perpendicuar(const Vector3& vector);


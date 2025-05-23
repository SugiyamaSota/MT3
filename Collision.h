#pragma once

///// 前方宣言 /////
struct Sphere;
struct Plane;
struct Vector3;
struct Segment;
struct Triangle;

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& s, const Plane& p);

bool IsCollision(const Segment& segment, const Plane& plane);

bool IsCollision(const Triangle& triangle, const Segment& segment);
#pragma once

///// 前方宣言 /////
struct Sphere;
struct Plane;
struct Vector3;
struct Segment;

bool isCollision(const Sphere& s1, const Sphere& s2);

bool isCollision(const Sphere& s, const Plane& p);

bool isCollision(const Segment& segment, const Plane& plane);


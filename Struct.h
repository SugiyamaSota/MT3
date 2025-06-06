﻿#pragma once

//4x4行列
struct Matrix4x4 {
	float m[4][4];
};

struct Vector2 {
	float x, y;
};

//三次元ベクトル
struct Vector3 {
	float x, y, z;
};

//球
struct Sphere {
	Vector3 center;
	float radius;
};

//直線
struct Line {
	Vector3 origin;
	Vector3 diff;
};

//半直線
struct Ray {
	Vector3 origin;
	Vector3 diff;
};

//線分
struct Segment {
	Vector3 origin;
	Vector3 diff;
};

//平面
struct Plane {
	Vector3 normal;
	float distance;
};

//三角形
struct Triangle {
	Vector3 vertices[3];
};

//AABB
struct AABB {
	Vector3 min;
	Vector3 max;
};
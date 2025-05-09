#pragma once

//4x4行列
struct Matrix4x4 {
	float m[4][4];
};

//三次元ベクトル
struct Vector3 {
	float x, y, z;
};

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

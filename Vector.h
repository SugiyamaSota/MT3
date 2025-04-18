#pragma once

struct Vector3 {
	float x, y, z;
};

//===計算関数===//
//加算
Vector3 Add(const Vector3& vector1, const Vector3& vector2);

//減算
Vector3 Subtract(const Vector3& vector1, const Vector3& vector2);

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& vector);

//内積
float Dot(const Vector3& vector1, const Vector3& vector2);

//長さ(ノルム)
float Length(const Vector3& vector);

//正規化
Vector3 Normalize(const Vector3& vector);

//===表示関数===//
static const int kVectorColumnWidth = 60;

void  VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

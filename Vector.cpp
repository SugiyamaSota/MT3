#include"Vector.h"
#include<math.h>
#include<Novice.h>

Vector3 Add(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result = {};
	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	result.z = vector1.z + vector2.z;
	return result;
}

Vector3 Subtract(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result = {};
	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& vector) {
	Vector3 result = {};
	result.x = scalar * vector.x;
	result.y = scalar * vector.y;
	result.z = scalar * vector.z;
	return result;
}

float Dot(const Vector3& vector1, const Vector3& vector2) {
	float result = {};
	result = vector1.x * vector2.x +
		vector1.y * vector2.y +
		vector1.z * vector2.z;
	return result;
}

float Length(const Vector3& vector) {
	float result = {};
	result = vector.x * vector.x +
		vector.y * vector.y +
		vector.z * vector.z;
	result = sqrtf(result);
	return result;
}

Vector3 Normalize(const Vector3& vector) {
	Vector3 result = {};
	float length = {};
	length = vector.x * vector.x +
		vector.y * vector.y +
		vector.z * vector.z;
	length = 1.0f / sqrtf(length);
	result.x = length * vector.x;
	result.y = length * vector.y;
	result.z = length * vector.z;
	return result;
}

void  VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}
﻿#pragma once
///// 前方宣言 /////
struct Vector3;
struct Segment;

///// 計算関数 /////
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

//外積
Vector3 Cross(const Vector3& vector1, const Vector3& vector2);

//正射影ベクトル
Vector3 Project(const Vector3& v1, Vector3& v2);

//最近接点
Vector3 ClosestPoint(const Vector3& point,Segment& segment);

//4頂点
Vector3 Perpendicuar(const Vector3& vector);

///// 描画関数 /////
static const int kVectorColumnWidth = 60;

void  VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

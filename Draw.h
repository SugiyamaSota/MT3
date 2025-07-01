#pragma once
#include<cstdint>

///// 前方宣言 /////
class Camera;
struct Sphere;
struct Plane;
struct Triangle;
struct AABB;
struct Vector3;

//グリッドの描画
void DrawGrid(Camera* camera);

//球体の描画
void DrawSphere(const Sphere& sphere, Camera* camera, uint32_t color);

//平面の描画
void DrawPlane(const Plane& plane, Camera* camera, uint32_t color);

//三角形の描画
void DrawTriangle(const Triangle& triangle, Camera* camera, uint32_t color);

//AABBの描画
void DrawAABB(const AABB& aabb, Camera* camera, uint32_t color);

void DrawBezier(const Vector3& controlPosint0, const Vector3& controlPosint1, const Vector3& controlPosint2,
	Camera* camera, uint32_t color);